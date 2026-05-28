#include <math.h>
#include <CG/Polygon/Point.h>

#include <CG/Polygon/Generator.h>
#include <CG/RNG/RNG.h>

namespace CG::Polygon
{
    bool Point::geq(const long double &a, const long double &b){return a-b >= -eps;}
    bool Point::leq(const long double & a, const long double &b){return b-a >= -eps;}
    bool Point::ge(const long double & a, const long double &b){return a-b > eps;}
    bool Point::le(const long double & a, const long double &b){return b-a > eps;}
    bool Point::eq(const long double & a, const long double &b){return abs(a-b) <= eps;}
    bool Point::neq(const long double & a, const long double &b){return abs(a-b) > eps;}

    Point::Point(): x(0), y(0){}

    Point::Point(const long double &_x, const long double &_y):x(_x), y(_y){}

    Point Point::operator +(const Point &p) const{return Point(x + p.x, y + p.y);}
    Point Point::operator -(const Point &p) const{return Point(x - p.x, y - p.y);}
    Point Point::operator *(const long double &k) const {return Point(x * k, y * k);}
    Point Point::operator /(const long double &k) const {return Point(x / k, y / k);}

    Point Point::operator += (const Point &p){*this = *this + p; return *this;}
    Point Point::operator -= (const Point &p){*this = *this - p; return *this;}
    Point Point::operator *= (const long double &k){*this = *this * k; return *this;}
    Point Point::operator /= (const long double &k){*this = *this / k; return *this;}
    Point& Point::operator = (const Point &p){
        if(this != &p){x = p.x; y = p.y;}
        return *this;
    }

    long double Point::dot(const Point &p) const{return x * p.x + y * p.y;}
    long double Point::cross(const Point &p) const{return x * p.y - y * p.x;}
    long double Point::norm() const{return x * x + y * y;}
    long double Point::length() const{return sqrtl(x * x + y * y);}
    Point Point::unit() const{return (*this) / length();}

    bool Point::operator==(const Point & p) const{return eq(x, p.x) && eq(y, p.y);}
    bool Point::operator!=(const Point & p) const{return !(*this == p);}
    bool Point::operator<(const Point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
    bool Point::operator>(const Point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
    bool Point::half(const Point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}

    long double Point::getX(){return x;}
    long double Point::getY(){return y;}



    Generator::Generator(const int &p)
    {
        marginTop = marginRight = 5e6;
        marginLeft = marginDown = -5e6;

        points.assign(p, Point());

        CG::RNG::RNG rng;

        for(int i = 0; i < p; ++i)
        {
            points[i] = Point((long double)rng.aleatorio(marginLeft, marginRight),
                            (long double)rng.aleatorio(marginDown, marginTop));
        }
    }

    Generator::Generator(int p, long long U, long long R, long long D, long long L)
    {
        if(U < D)std::swap(U, D);
        if(R < L)std::swap(R, L);
        marginTop = U;
        marginRight = R;
        marginLeft = L;
        marginDown = D;

        points.assign(p, Point());

        CG::RNG::RNG rng;

        for(int i = 0; i < p; ++i)
        {
            points[i] = Point(rng.aleatorio(marginLeft, marginRight),
                            rng.aleatorio(marginDown, marginTop));
        }
    }

    void Generator::normalize()
    {
        long double w = marginRight - marginLeft;
        long double h = marginTop - marginDown;
        long double x, y;

        for(int i = 0; i < points.size(); ++i)
        {
            points[i] -= Point(marginLeft, marginDown);

            x = (points[i].getX() / w) - 0.5f;
            y = (points[i].getY() / h) - 0.5f;

            points[i] = Point(x,y);
        }
    }

    void Generator::convexHull()
    {
        std::sort(points.begin(), points.end());
        std::vector<Point> L, U;
        for(int i = 0; i < points.size(); i++){
            while(L.size() >= 2 && Point::leq((L[L.size() - 2] - points[i]).cross(L[L.size() - 1] - points[i]), 0)){
                L.pop_back();
            }
            L.push_back(points[i]);
        }
        for(int i = points.size() - 1; i >= 0; i--){
            while(U.size() >= 2 && Point::leq((U[U.size() - 2] - points[i]).cross(U[U.size() - 1] - points[i]), 0)){
                U.pop_back();
            }
            U.push_back(points[i]);
        }
        L.pop_back();
        U.pop_back();
        L.insert(L.end(), U.begin(), U.end());
        std::swap(points, L);
    }

    std::vector<Point> Generator::getPoints(){return points;}

}