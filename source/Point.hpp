#ifndef _POINT_
#define _POINT_

#include <cmath>
using namespace std;

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
};

inline bool operator <(const Point& lhs, const Point& rhs) { return lhs.m_x < rhs.m_x && lhs.m_y < rhs.m_y; }
inline bool operator ==(const Point& lhs, const Point& rhs) { return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y; }
inline Point max(const Point& p1, const Point& p2) { return p1<p2?p2:p1; }
inline Point max(const Point& p1, const Point& p2, const Point& p3) { return max(max(p1,p2),p3); }

#endif