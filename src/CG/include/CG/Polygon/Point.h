#pragma once

namespace CG::Polygon
{
    class Point
    {
        private:
            long double x, y;
        public:
            constexpr static long double eps = 1e-9;
            static bool geq(const long double &a, const long double &b);
            static bool leq(const long double &a, const long double &b);
            static bool ge(const long double &a, const long double &b);
            static bool le(const long double &a, const long double &b);
            static bool eq(const long double &a, const long double &b);
            static bool neq(const long double &a, const long double &b);

            Point();
            Point(const long double &_x, const long double &_y);

            Point operator +(const Point &p) const;
            Point operator -(const Point &p) const;
            Point operator *(const long double &k) const;
            Point operator /(const long double &k) const;

            Point operator += (const Point &p);
            Point operator -= (const Point &p);
            Point operator *= (const long double &k);
            Point operator /= (const long double &k);
            Point& operator = (const Point &p);

            long double dot(const Point &p) const;
            long double cross(const Point &p) const;
            long double norm() const;
            long double length() const;
            Point unit() const;

            bool operator==(const Point & p) const;
            bool operator!=(const Point & p) const;
            bool operator<(const Point & p) const;
            bool operator>(const Point & p) const;
            bool half(const Point & p) const;

            long double getX();
            long double getY();
    };
}