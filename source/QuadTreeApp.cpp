#include <map>
#include <math.h>
using namespace std;

#include "QuadTreeApp.hpp"

QuadTreeApp::QuadTreeApp()
{
}

QuadTreeApp::~QuadTreeApp()
{
}

void QuadTreeApp::init_quadtree(int w) 
{
	// init
	m_quadtree = QuadTree(w);

	// message
	cout << "initialized a quadtree of width " << pow(2, w) << endl;
}

void QuadTreeApp::display()
{
	// display
}

void QuadTreeApp::list_rectangles()
{
	// print all rectangles in m_rects
	std::map<std::string, Rect>::iterator i;
	Rect* r;
	
	for(i = m_rects.begin(); i != m_rects.end(); i++) {
		r = &i->second;

	    cout << i->first << " ";
	    cout << r->m_corner.m_x << " " << r->m_corner.m_y << " ";
	    cout << r->m_size.m_x << " " << r->m_size.m_y;
	    cout << endl;
    }
}

void QuadTreeApp::create_rectangle(std::string r, int x1, int x2, int y1, int y2)
{
	// create and add rectangle to rects
	Rect rect = Rect(r, x1, x2, y1, y2);
	m_rects[r] = rect;

	// message
	cout << "created rectangle " << r << endl;
}

void QuadTreeApp::create_rectangle_random(std::string r)
{
	// create and add random rectangle to rects
}

void QuadTreeApp::rectangle_search(std::string r)
{
	m_quadtree.rectangle_search(r);
}

void QuadTreeApp::move(std::string r, int cx, int cy)
{
	m_quadtree.move(r, cx, cy);
}

void QuadTreeApp::insert(std::string r)
{
	Rect rect = m_rects.find(r)->second;
	m_quadtree.insert(rect);
}

void QuadTreeApp::search_point(int x, int y)
{
	m_quadtree.search_point(x, y);
}

void QuadTreeApp::delete_rectangle(std::string r)
{
	m_quadtree.delete_rectangle(r);
}

void QuadTreeApp::delete_point(int x, int y)
{
	m_quadtree.delete_point(x, y);
}

void QuadTreeApp::touch(std::string r)
{
}

void QuadTreeApp::within(std::string name, int dist)
{
}

void QuadTreeApp::horiz_neighbor(string name)
{
}

void QuadTreeApp::vert_neighbor(string name)
{
}

void QuadTreeApp::nearest_rectangle(int x, int y)
{
}

void QuadTreeApp::window(int x1, int x2, int y1, int y2)
{
}

void QuadTreeApp::nearest_neighbor(string name)
{
}

void QuadTreeApp::lexically_greater_nearest_neighbor(string name)
{
}

void QuadTreeApp::label()
{
}

