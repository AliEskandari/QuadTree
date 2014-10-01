#include <string>
using namespace std;

#include "QuadTree.hpp"

/******************************************************************************
 * Point
 *****************************************************************************/
Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

Point::Point()
{
}

Point::~Point()
{
}

/******************************************************************************
 * Rect
 *****************************************************************************/
Rect::Rect(std::string r, int x1, int x2, int y1, int y2)
{
	m_name 		= r;
	m_corner 	= Point(x1, y1);
	m_size 		= Point(x2, y2);
	m_label 	= 0;
	m_son 		= nullptr;
}

Rect::Rect()
{
}

Rect::~Rect()
{
}

/******************************************************************************
 * QuadNode
 *****************************************************************************/
QuadTree::QuadNode::QuadNode(Rect& data, Point pt, Quadrant quadrant)
{
	m_pt 		= pt;
	m_type 		= BLACK;
	m_data 		= data;
	m_son 		= nullptr;
	m_quadrant 	= quadrant;
}

QuadTree::QuadNode::QuadNode()
{
}

QuadTree::QuadNode::~QuadNode()
{
}

/******************************************************************************
 * QuadTree
 *****************************************************************************/

/* Private */

QuadTree::QuadNode* QuadTree::insert(QuadNode* root, Rect data)
{
	if (root == NULL) return new QuadNode(data);
	else
	{	Point root_loc = root->m_pt;
		Point r_corner = data.m_corner;

//		if ((r_corner.m_x > root_loc.m_x) && (r_corner.m_y > root_loc.m_y)) root->m_son[0] = insert();
//		{
//
//		}

		return NULL;
	}
}

/* Public */

 
QuadTree::QuadTree(int width) : m_rect(NULL)
{
	m_root = new QuadNode()
}

QuadTree::QuadTree() : m_root(NULL), m_rect(NULL)
{
}

QuadTree::~QuadTree()
{
	delete m_root;
	delete m_rect;
}

void QuadTree::rectangle_search(std::string r)
{
	
}     

void QuadTree::move(std::string r, int cx, int cy)
{

}

void QuadTree::insert(Rect data)
{
	m_root = this->insert(m_root, data);
}

void QuadTree::search_point(int x, int y)
{

}

void QuadTree::delete_rectangle(std::string r)
{

}

void QuadTree::delete_point(int x, int y)
{

}



