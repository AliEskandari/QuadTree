#ifndef _POINT_
#define _POINT_

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    Point() : m_x(0), m_y(0) {}
    ~Point();

    int m_x;
    int m_y;
};

#endif