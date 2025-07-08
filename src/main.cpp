

#include <iostream>
#include <vector>
#include <thread>
#include <glm/glm.hpp>
#include "Ray.hpp"

using ColorRGB = glm::ivec3;


glm::vec3 TransformPointToRHS(const glm::vec3& l_point, const float l_width, const float l_height)
{
	return glm::vec3(l_point.x - l_width/2.f, -l_point.y + l_height/2.f, l_point.z);
}

ColorRGB GenerateColorBasedOnRay(const RayTracer::Ray& l_ray)
{
	glm::vec3 lv_unitRayDirection = glm::normalize(l_ray.m_direction);
	float lv_blendValue = 0.5f * (lv_unitRayDirection.y + 1.f);
	auto lv_resultf = (1.f - lv_blendValue) * glm::vec3(1.f, 1.f, 1.f) + lv_blendValue * glm::vec3(0.5f, 0.7f, 1.f);

	return ColorRGB((int)(lv_resultf.x * 255.f), (int)(lv_resultf.y*255.f), (int)(lv_resultf.z*255.f));
}


int main()
{
	using namespace RayTracer;

	constexpr uint32_t lv_height = 512U;
	constexpr uint32_t lv_width = 512U;
	constexpr uint32_t lv_maxOfEachComponent = 255U;
	const uint32_t lv_maxNumThreads = 8U;
	constexpr uint32_t lv_heightThread = lv_height / lv_maxNumThreads;


	std::vector<Ray> lv_rays{};
	lv_rays.resize((lv_width)*(lv_height));

	std::vector<ColorRGB> lv_finalColors{};
	lv_finalColors.resize((lv_width) * (lv_height));

	auto lv_threadLambdaRays = [&lv_rays, lv_heightThread, lv_width, lv_height](const uint32_t l_beginHeightThread)
		{
			const uint32_t lv_endThreadHeight = l_beginHeightThread + lv_heightThread;
			for (uint32_t i = 0; i < (lv_width); ++i) {
				for (uint32_t j = l_beginHeightThread; j < lv_endThreadHeight; ++j) {
					lv_rays[j * (lv_width) + i].m_direction = TransformPointToRHS(glm::vec3((float)i, (float)j, -1.f), lv_width, lv_height);
				}
			}
		};

	auto lv_threadLambdaGenerateColors = [&lv_finalColors, &lv_rays, lv_heightThread, lv_width, lv_height](const uint32_t l_beginHeightThread) -> void
		{
			const uint32_t lv_endThreadHeight = l_beginHeightThread + lv_heightThread;
			for (uint32_t i = 0; i < (lv_width); ++i) {
				for (uint32_t j = l_beginHeightThread; j < lv_endThreadHeight; ++j) {
					lv_finalColors[j * (lv_width) + i] = GenerateColorBasedOnRay(lv_rays[j * (lv_width) + i]);
				}
			}
		};
	
	std::vector<std::thread> lv_threadPool{};
	lv_threadPool.resize(lv_maxNumThreads);
	for (uint32_t i = 0U; i < lv_maxNumThreads; ++i) {
		lv_threadPool[i] = std::thread(lv_threadLambdaRays, i*lv_heightThread);
	}

	for (uint32_t i = 0U; i < lv_maxNumThreads; ++i) {
		lv_threadPool[i].join();
		lv_threadPool[i] = std::thread(lv_threadLambdaGenerateColors, i*lv_heightThread);
	}

	for (auto& lv_thread : lv_threadPool) {
		lv_thread.join();
	}
	
	std::cout << "P3" << std::endl;
	std::cout << lv_width << " " << lv_height << std::endl;
	std::cout << lv_maxOfEachComponent << std::endl;

	for (const auto& lv_color : lv_finalColors) {
		std::cout << lv_color.r << " " << lv_color.g << " " << lv_color.b << std::endl;
	}

	return 0;
}