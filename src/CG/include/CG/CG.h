#pragma once
#include <CG/Polygon/Generator.h>

namespace CG
{
    class CG
    {
        public:
            CG();

            void createPolygon(const int &p);

            void createPolygon(const int &p, const long long &U, const long long &R, const long long &D, const long long &L);

            std::vector<Polygon::Point> getPoints();

            void convexHull();

            void normalize();
        private:
            Polygon::Generator *generator;
    };
}