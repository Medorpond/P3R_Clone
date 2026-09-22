#include "Core/P3R_Utils.h"

namespace Utils
{
	bool RollChance(const float Probability)
	{
		return Probability >= 1.f || FMath::FRand() < Probability;
	}
	
}
