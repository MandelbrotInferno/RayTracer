#pragma once


#include <vector>
#include "Sphere.hpp"


namespace RayTracer
{
	struct GeometryListInScene final
	{
		std::vector<Sphere> m_spheres{};
	};
}