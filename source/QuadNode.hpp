#ifndef _QUADNODE_
#define _QUADNODE_

#include "Rect.hpp"

enum Direction {LEFT, RIGHT};
enum Quaddrant {NW, NE, SW, SE};
enum Nodetype {
    GRAY, 	/* internal node */
    BLACK, 	/* leaf node w/ data */
    WHITE	/* leaf node w/o data */
};

class QuadNode
{
public:
    QuadNode(Rect bounds, int label);
    QuadNode();
    ~QuadNode();

    Rect		m_bounds;                       /* bounds of node */
    Nodetype    m_type;                        	/* GRAY, BLACK, WHITE */
    Rect        m_rect;                        	/* pointer to rectangle, contained in this quadrant */
    int         m_label;                        /* user for op #11: LABEL() */

    QuadNode*   m_nw;                          	/* four principle quadrant directions */
    QuadNode*   m_ne;
    QuadNode*   m_sw;
    QuadNode*   m_se;

    bool        split();
};

enum CompareAxis {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
};

class CompareDistanceToRect {
    Rect target;
    CompareAxis m_compare_axis;

public:
    CompareDistanceToRect(Rect target, CompareAxis compare_axis) : target(target), m_compare_axis(compare_axis) {}

    /* return true if n1 should be ordered after n2 */
    bool operator()(QuadNode* const & n1, QuadNode* const & n2) {

        if (m_compare_axis == HORIZONTAL)
        {
            int hd1 = max(0, target.horiz_distance(n1->m_bounds));
            int hd2 = max(0, target.horiz_distance(n2->m_bounds));
            if (hd1 == hd2) return n1->m_label > n2->m_label;
            else return hd1 > hd2;
        }
        else if (m_compare_axis == VERTICAL)
        {
            int vd1 = max(0, target.vert_distance(n1->m_bounds));
            int vd2 = max(0, target.vert_distance(n2->m_bounds));
            if (vd1 == vd2) return n1->m_label > n2->m_label;
            else return vd1 > vd2;
        }
        else
        {
            int d1 = max(0, target.distance(n1->m_bounds));
            int d2 = max(0, target.distance(n2->m_bounds));
            if (d1 == d2) return n1->m_label > n2->m_label;
            else return d1 > d2;
        }
    }
};

class CompareDistanceToPoint {
    Point target;

public:
    CompareDistanceToPoint(Point target) : target(target) {}

    bool operator() (QuadNode* const & n1, QuadNode* const & n2) {

        int d1 = n1->m_bounds.distance(target);
        int d2 = n2->m_bounds.distance(target);
        if (d1 == d2) return n1->m_label > n2->m_label;
        else return d1 > d2;
    }
};

#endif