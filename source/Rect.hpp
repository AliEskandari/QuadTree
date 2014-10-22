#ifndef _RECT_
#define _RECT_

#include <string>
#include <algorithm>
using namespace std;

#include "Point.hpp"

/**
* Note that a rectangle is closed on its left and bottom side and open on its top and right side
*/
class Rect
{
public:
    Rect(string r, int x1, int y1, int x2, int y2) :
            m_name(r), m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_left(0), m_right(0), m_w(x2-x1), m_h(y2-y1) {}

    Rect(int x1, int y1, int x2, int y2) :
            m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_left(0), m_right(0), m_w(x2-x1), m_h(y2-y1) {}

    Rect() :
            m_x1(0), m_y1(0), m_x2(0), m_y2(0), m_left(0), m_right(0) {}

    ~Rect();

    string    		m_name;                 /* name of rectangle */
    int             m_x1, m_y1, m_x2, m_y2; /* lower left corner pt, upper right corner point */
    Rect*          	m_left;                 /* left and right sons */
    Rect*			m_right;
    int             m_w,m_h;

    inline bool contains(Rect& r) { return ((m_x1 <= r.m_x1) && (m_y1 <= r.m_y1) && (r.m_x2 <= m_x2) && (r.m_y2 <= m_y2)); }
    inline bool intersects(Rect& r) { return ( max(m_x1, r.m_x1) < min(m_x2, r.m_x2) && max(m_y1, r.m_y1) < min(m_y2, r.m_y2)); }
    inline bool contains(Point& p) { return (m_x1 <= p.m_x && m_y1 <= p.m_y && p.m_x < m_x2 && p.m_y < m_y2); }

    inline bool operator ==(const Rect& r) { return m_x1 == r.m_x1 && m_y1 == r.m_y1 && m_x2 == r.m_x2 && m_y2 == r.m_y2; }
    inline bool operator !=(const Rect& r) { return !(*this == r); }
};

namespace std
{
    template <>
    struct less<Rect>
    {
        bool operator() (const Rect lhs, const Rect rhs)
        {
            return lhs.m_name < rhs.m_name;
        }
    };
}


#endif