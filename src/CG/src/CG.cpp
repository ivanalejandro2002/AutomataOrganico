#include <iostream>
#include <CG/CG.h>

namespace CG
{
    CG::CG()
    {
        generator = nullptr;
    }

    void CG::createPolygon(const int &p, const long long &U, const long long &R, const long long &D, const long long &L)
    {
        generator = new Polygon::Generator(p, U, R, D, L);
    }

    void CG::createPolygon(const int &p)
    {
        generator = new Polygon::Generator(p);
    }

    void CG::normalize(){generator->normalize();}

    void CG::convexHull(){generator->convexHull();}

    std::vector<Polygon::Point> CG::getPoints(){return generator->getPoints();}
}