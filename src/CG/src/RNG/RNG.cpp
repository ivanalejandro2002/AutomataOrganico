#include <CG/RNG/RNG.h>

namespace CG::RNG
{
    RNG::RNG():rng(std::chrono::steady_clock::now().time_since_epoch().count()){}

    long long RNG::aleatorio(const long long &a, const long long &b)
    {
        std::uniform_int_distribution<long long> dist(a, b);
	    return dist(rng);
    }
}