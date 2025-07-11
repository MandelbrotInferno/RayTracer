#pragma once



#include <glm/glm.hpp>
#include "HitRecord.hpp"



namespace RayTracer
{
	struct Ray;

	struct Sphere final
	{
		explicit Sphere(const glm::vec3& l_origin, const float l_radius);

		HitRecord TestIntersection(const Ray& l_ray, const float l_minT, const float l_maxT) const;

		glm::vec3 m_origin{};
		float m_radius{};
	};

}