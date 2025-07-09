#pragma once



#include <glm/glm.hpp>


namespace RayTracer
{

	struct Sphere final
	{
		glm::vec3 m_origin{};
		float m_radius{};
	};

}