#pragma once



#include <glm/glm.hpp>

namespace RayTracer
{
	struct RayTracer final
	{

		RayTracer(const glm::vec3& l_origin, const glm::vec3& l_dir);


		glm::vec3 At(const float l_t) const;

		glm::vec3 m_origin{};
		glm::vec3 m_direction{};

	};
}