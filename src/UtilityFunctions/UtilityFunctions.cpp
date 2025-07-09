

#include "UtilityFunctions/UtilityFunctions.hpp"



namespace RayTracer
{
	namespace UtilityFunctions
	{
		glm::vec3 TransformPointToRHS(const glm::vec3& l_point, const float l_width, const float l_height)
		{
			return glm::vec3((l_point.x - l_width / 2.f), (-l_point.y + l_height / 2.f), l_point.z);
		}

		ColorRGB GenerateColorBasedOnRay(const RayTracer::Ray& l_ray)
		{
			glm::vec3 lv_unitRayDirection = glm::normalize(l_ray.m_direction);
			float lv_blendValue = 0.5f * (lv_unitRayDirection.y + 1.f);
			auto lv_resultf = (1.f - lv_blendValue) * glm::vec3(1.f, 1.f, 1.f) + lv_blendValue * glm::vec3(0.5f, 0.7f, 1.f);

			return ColorRGB((int)(lv_resultf.x * 255.f), (int)(lv_resultf.y * 255.f), (int)(lv_resultf.z * 255.f));
		}

		void WriteColorToOutputStream(std::ostream& l_cout, const std::span<ColorRGB> l_finalColors, const uint32_t l_width, const uint32_t l_height)
		{
			l_cout << "P3" << std::endl;
			l_cout << l_width << " " << l_height << std::endl;
			l_cout << 255 << std::endl;

			for (const auto& l_rgb : l_finalColors) {
				l_cout << l_rgb.r << " " << l_rgb.g << " " << l_rgb.b << "\n";
			}

			l_cout << std::flush;
		}
	}
}