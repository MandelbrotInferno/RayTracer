#pragma once



#include <random>


namespace RayTracer
{

	class RandomNumGenerator final
	{
	public:

		RandomNumGenerator(const float l_minInterval, const float l_maxInterval);

		float GeneratorRandNumber();

	private:
		std::uniform_real_distribution<float> m_distribution;
		std::mt19937 m_generator{};
	};

}