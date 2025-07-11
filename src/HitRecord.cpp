


#include "HitRecord.hpp"
#include "Ray.hpp"

namespace RayTracer
{

	void HitRecord::SetFaceNormal(const Ray& l_ray, const glm::vec3& l_unitOutwardNormal)
	{
		const float lv_dot = glm::dot(l_ray.m_direction, l_unitOutwardNormal);

		m_faceNormal = (lv_dot < 0.f) ? true : false;
	}

}