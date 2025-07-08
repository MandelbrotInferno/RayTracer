#pragma once



#include <glm/glm.hpp>

namespace RayTracer
{
	struct Ray final
	{

		Ray(const glm::vec3& l_origin, const glm::vec3& l_dir);
		Ray() = default;

		glm::vec3 At(const float l_t) const;

		glm::vec3 m_origin{};
		glm::vec3 m_direction{};

	};
}