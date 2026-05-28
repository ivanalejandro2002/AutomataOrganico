#pragma once
#include <vector>
#include <algorithm>
#include <CG/Polygon/Point.h>

namespace CG::Polygon
{
    class Generator
    {
        private:
            std::vector<Point> points;
            long long marginTop, marginRight, marginDown, marginLeft;
        public:
            Generator(const int &p);
            Generator(int p, long long U, long long R, long long D, long long L);
            
            void normalize();
            void convexHull();
            std::vector<Point> getPoints();
    };
}