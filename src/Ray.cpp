

#include "Ray.hpp"



namespace RayTracer
{

	RayTracer::RayTracer(const glm::vec3& l_origin, const glm::vec3& l_dir)
		:m_origin(l_origin), m_direction(l_dir)
	{

	}


	glm::vec3 RayTracer::At(const float l_t) const
	{
		return m_origin + l_t * m_direction;
	}

}