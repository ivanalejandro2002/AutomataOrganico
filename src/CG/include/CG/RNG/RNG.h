#pragma once

#include <random>
#include <chrono>

namespace CG::RNG
{
    class RNG
    {
        private:
            std::mt19937_64 rng;
        public:
            RNG();

            long long aleatorio(const long long &a, const long long &b);
    };
}