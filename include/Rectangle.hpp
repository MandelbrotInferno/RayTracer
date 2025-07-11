#pragma once



#include <glm/glm.hpp>


namespace RayTracer
{
	struct Rectangle final
	{
		glm::vec3 m_min{};
		glm::vec3 m_max{};
	};
}