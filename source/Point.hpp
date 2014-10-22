#ifndef _POINT_
#define _POINT_

#include <cmath>

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    Point() : m_x(0), m_y(0) {}
    ~Point();

    int m_x;
    int m_y;

    inline int magnitude() { return (int) pow(pow(m_x, 2) + pow(m_y, 2),.5); }

    inline const Point operator -(Point p) { return Point(m_x - p.m_x, m_y - p.m_y); }
    inline bool operator <(const Point& p) const { return (m_x < p.m_x && m_y < p.m_y); }

//    static inline Point max(Point a, Point b) { return a < b ? b : a; }
};


#endif