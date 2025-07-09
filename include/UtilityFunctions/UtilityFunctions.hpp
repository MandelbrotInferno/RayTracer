#pragma once



#include <glm/glm.hpp>
#include <span>
#include <ostream>
#include "Ray.hpp"


namespace RayTracer
{
	namespace UtilityFunctions
	{
		using ColorRGB = glm::ivec3;


		glm::vec3 TransformPointToRHS(const glm::vec3& l_point, const float l_width, const float l_height);

		ColorRGB GenerateColorBasedOnRay(const RayTracer::Ray& l_ray);

		void WriteColorToOutputStream(std::ostream& l_cout, const std::span<ColorRGB> l_finalColors, const uint32_t l_width, const uint32_t l_height);
	}
}