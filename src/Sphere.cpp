


#include "Sphere.hpp"
#include "Ray.hpp"
#include <cmath>	

namespace RayTracer
{

	Sphere::Sphere(const glm::vec3& l_origin, const float l_radius)
		:m_origin(l_origin), m_radius(l_radius)
	{

	}


	HitRecord Sphere::TestIntersection(const Ray& l_ray, const float l_minT, const float l_maxT) const
	{
		HitRecord lv_hitRecord{};

		const glm::vec3 lv_diffOrigins = m_origin - l_ray.m_origin;

		const float lv_a = glm::dot(l_ray.m_direction, l_ray.m_direction);
		const float lv_b = -2 * glm::dot(l_ray.m_direction, lv_diffOrigins);
		const float lv_c = glm::dot(lv_diffOrigins, lv_diffOrigins) - (m_radius * m_radius);

		const float lv_discriminant = lv_b * lv_b - 4.f * lv_a * lv_c;

		if (lv_discriminant < 0.f) {
			return lv_hitRecord;
		}
		else {
			const float lv_sqrtDiscriminant = std::sqrtf(lv_discriminant);
			const float lv_t1 = (-lv_b + lv_sqrtDiscriminant) / (2 * lv_a);
			const float lv_t2 = (-lv_b - lv_sqrtDiscriminant) / (2 * lv_a);

			if ((l_minT <= lv_t1 && lv_t1 <= l_maxT) || (l_minT <= lv_t2 && lv_t2 <= l_maxT)) {
				float lv_t = std::fmin(lv_t1, lv_t2);
				lv_hitRecord.m_isHit = true;
				glm::vec3 lv_unitOutwardNormal{};
				if (l_minT <= lv_t && lv_t <= l_maxT) {
					lv_hitRecord.m_t = lv_t;
					lv_hitRecord.m_pointOfIntersection = l_ray.At(lv_t);
					lv_unitOutwardNormal = (lv_hitRecord.m_pointOfIntersection - m_origin) / m_radius;
					lv_hitRecord.SetFaceNormal(l_ray, lv_unitOutwardNormal);
				}
				else {
					lv_t = std::fmax(lv_t1, lv_t2);
					lv_hitRecord.m_t = lv_t;
					lv_hitRecord.m_pointOfIntersection = l_ray.At(lv_t);
					lv_unitOutwardNormal = (lv_hitRecord.m_pointOfIntersection - m_origin) / m_radius;
					lv_hitRecord.SetFaceNormal(l_ray, lv_unitOutwardNormal);
				}

				lv_hitRecord.m_normal = (false == lv_hitRecord.m_faceNormal) ? -lv_unitOutwardNormal : lv_unitOutwardNormal;

				return lv_hitRecord;
			}
			else {
				return lv_hitRecord;
			}
		}
	}

}