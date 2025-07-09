

#include <iostream>
#include <vector>
#include <thread>
#include "UtilityFunctions/UtilityFunctions.hpp"


int main()
{
	using namespace RayTracer;

	constexpr uint32_t lv_height = 512U;
	constexpr uint32_t lv_width = 912U;
	constexpr uint32_t lv_maxNumThreads = 8U;
	constexpr uint32_t lv_heightThread = lv_height / lv_maxNumThreads;
	constexpr float lv_viewPortWidth = 3.5546875f;
	constexpr float lv_viewPortHeight = 2.f;
	constexpr float lv_deltaX = lv_viewPortWidth / lv_width;
	constexpr float lv_deltaY = lv_viewPortHeight / lv_height;

	std::vector<Ray> lv_rays{};
	lv_rays.resize((lv_width)*(lv_height));

	std::vector<UtilityFunctions::ColorRGB> lv_finalColors{};
	lv_finalColors.resize((lv_width) * (lv_height));

	auto lv_threadLambdaRays = [&lv_rays, lv_heightThread, lv_width, lv_height, lv_deltaX, lv_deltaY, lv_viewPortHeight, lv_viewPortWidth](const uint32_t l_beginHeightThread)
		{
			const uint32_t lv_endThreadHeight = l_beginHeightThread + lv_heightThread;
			for (uint32_t i = 0; i < (lv_width); ++i) {
				for (uint32_t j = l_beginHeightThread; j < lv_endThreadHeight; ++j) {
					lv_rays[j * (lv_width) + i].m_direction = UtilityFunctions::TransformPointToRHS(glm::vec3((float)i * lv_deltaX, (float)j*lv_deltaY, -1.f), lv_viewPortWidth, lv_viewPortHeight);
				}
			}
		};


	auto lv_threadLambdaGenerateColors = [&lv_finalColors, &lv_rays, lv_heightThread, lv_width, lv_height](const uint32_t l_beginHeightThread) -> void
		{
			const uint32_t lv_endThreadHeight = l_beginHeightThread + lv_heightThread;
			for (uint32_t i = 0; i < (lv_width); ++i) {
				for (uint32_t j = l_beginHeightThread; j < lv_endThreadHeight; ++j) {
					lv_finalColors[j * (lv_width) + i] = UtilityFunctions::GenerateColorBasedOnRay(lv_rays[j * (lv_width) + i]);
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
	
	UtilityFunctions::WriteColorToOutputStream(std::cout, lv_finalColors, lv_width, lv_height);

	return 0;
}