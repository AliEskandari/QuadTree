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

#endif