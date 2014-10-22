#include "QuadNode.hpp"

/******************************************************************************
* QuadNode
*****************************************************************************/
QuadNode::QuadNode(Rect bounds, int label) {
    m_bounds 	= bounds;
    m_type 		= WHITE;
    m_label     = label;

    m_nw		= nullptr;
    m_ne		= nullptr;
    m_sw		= nullptr;
    m_se		= nullptr;
}
QuadNode::QuadNode() {}
QuadNode::~QuadNode() {}

/**********************************************************
* Split node into 4 quadrants and re-inserts rect into 4 quadrants
*
* RETURN: true if successful, false otherwise
**********************************************************/
bool QuadNode::split() {

    m_sw = new QuadNode(Rect(m_bounds.m_x1, m_bounds.m_y1, m_bounds.m_x1 + m_bounds.m_w/2, m_bounds.m_y1 + m_bounds.m_h/2), 4*m_label + 3);
    m_se = new QuadNode(Rect(m_bounds.m_x1 + m_bounds.m_w/2, m_bounds.m_y1, m_bounds.m_x2, m_bounds.m_y1 + m_bounds.m_h/2), 4*m_label + 4);
    m_nw = new QuadNode(Rect(m_bounds.m_x1, m_bounds.m_y1 + m_bounds.m_h/2, m_bounds.m_x1 + m_bounds.m_w/2, m_bounds.m_y2), 4*m_label + 1);
    m_ne = new QuadNode(Rect(m_bounds.m_x1 + m_bounds.m_w/2, m_bounds.m_y1 + m_bounds.m_h/2, m_bounds.m_x2, m_bounds.m_y2), 4*m_label + 2);

    /* if data does not enter node's bounds then return */
    if (m_nw->m_bounds.intersects(m_rect)) {
        m_nw->m_type = BLACK;
        m_nw->m_rect = m_rect;
    }
    if (m_ne->m_bounds.intersects(m_rect)) {
        m_ne->m_type = BLACK;
        m_ne->m_rect = m_rect;
    }
    if (m_sw->m_bounds.intersects(m_rect)) {
        m_sw->m_type = BLACK;
        m_sw->m_rect = m_rect;
    }
    if (m_se->m_bounds.intersects(m_rect)) {
        m_se->m_type = BLACK;
        m_se->m_rect = m_rect;
    }

    return true;
}