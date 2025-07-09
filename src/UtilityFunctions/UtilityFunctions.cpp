

#include "UtilityFunctions/UtilityFunctions.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include <limits>


namespace RayTracer
{
	namespace UtilityFunctions
	{
		glm::vec3 TransformPointToRHS(const glm::vec3& l_point, const float l_width, const float l_height)
		{
			return glm::vec3((l_point.x - l_width / 2.f), (-l_point.y + l_height / 2.f), l_point.z);
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

		float ClosestIntersectionPointSphereRay(const Ray& l_ray, const Sphere& l_sphere)
		{
			const glm::vec3 lv_diffOrigins = l_sphere.m_origin - l_ray.m_origin;
			
			const float lv_a = glm::dot(l_ray.m_direction, l_ray.m_direction);
			const float lv_b = -2*glm::dot(l_ray.m_direction, lv_diffOrigins);
			const float lv_c = glm::dot(lv_diffOrigins, lv_diffOrigins) - (l_sphere.m_radius*l_sphere.m_radius);

			const float lv_discriminant = lv_b * lv_b - 4.f * lv_a * lv_c;

			if (lv_discriminant < 0.f) {
				return std::numeric_limits<float>::infinity();
			}
			else {
				const float lv_sqrtDiscriminant = std::sqrtf(lv_discriminant);
				const float lv_t1 = (-lv_b + lv_sqrtDiscriminant) / (2*lv_a);
				const float lv_t2 = (-lv_b - lv_sqrtDiscriminant) / (2 * lv_a);

				if (lv_t1 > 0.f || lv_t2 > 0.f) {
					float lv_t = std::min(lv_t1, lv_t2);
					if (lv_t <= 0.f) {
						return std::max(lv_t1, lv_t2);
					}
					else {
						return lv_t;
					}
				}
				else {
					return std::numeric_limits<float>::infinity();
				}
			}
		}


		ColorRGB GenerateColorBasedOnRay(const RayTracer::Ray& l_ray, const Sphere& l_sphere)
		{
			if (true == ClosestIntersectionPointSphereRay(l_ray, l_sphere)) {
				return ColorRGB(255, 0, 0);
			}

			glm::vec3 lv_unitRayDirection = glm::normalize(l_ray.m_direction);
			float lv_blendValue = 0.5f * (lv_unitRayDirection.y + 1.f);
			auto lv_resultf = (1.f - lv_blendValue) * glm::vec3(1.f, 1.f, 1.f) + lv_blendValue * glm::vec3(0.5f, 0.7f, 1.f);

			return ColorRGB((int)(lv_resultf.x * 255.f), (int)(lv_resultf.y * 255.f), (int)(lv_resultf.z * 255.f));
		}
	}
}