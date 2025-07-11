



#include "RandomNumGenerator.hpp"


namespace RayTracer
{
	RandomNumGenerator::RandomNumGenerator(const float l_minInterval, const float l_maxInterval)
		:m_distribution(l_minInterval, l_maxInterval)
	{

	}

	float RandomNumGenerator::GeneratorRandNumber()
	{
		return m_distribution(m_generator);
	}
}