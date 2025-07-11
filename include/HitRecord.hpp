#pragma once




#include <glm/glm.hpp>



namespace RayTracer
{

	struct Ray;

	struct HitRecord final
	{
		glm::vec3 m_normal{};
		glm::vec3 m_pointOfIntersection{};
		float m_t{};
		bool m_isHit{false};
		bool m_faceNormal{false};

		void SetFaceNormal(const Ray& l_ray, const glm::vec3& l_unitOutwardNormal);
	};

}