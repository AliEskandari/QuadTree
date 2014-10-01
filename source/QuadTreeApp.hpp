#ifndef _QUADTREEAPP_
#define _QUADTREEAPP_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "QuadTree.hpp"

class QuadTreeApp
{
private:
	QuadTree m_quadtree;
	std::map<std::string, Rect> m_rects;
public:
	/* Part 3 */
	QuadTreeApp();
	~QuadTreeApp();

	void init_quadtree(int width);											// op 1
	void display();															// op 2
	void list_rectangles();													// op 3
	void create_rectangle(string name, int x1, int x2, int y1, int y2);		// op 4
	void create_rectangle_random(string name);								// op 4

	void rectangle_search(string name); 									// op 5
	void move(string name, int cx, int cy);									// ? 
	void insert(string name);												// op 6
	void search_point(int x, int y);										// op 7
	void delete_rectangle(string name);										// op 8
	void delete_point(int x, int y);										// op 8

	/* Part 4 */
	void touch(string name);												// op 9
	void within(string name, int dist);										// op 10
	void horiz_neighbor(string name);										// op 11
	void vert_neighbor(string name);										// op 11
	void nearest_rectangle(int x, int y);									// op 12
	void window(int x1, int x2, int y1, int y2);							// op 13
	void nearest_neighbor(string name);										// op 14
	void lexically_greater_nearest_neighbor(string name);					// op 15
	void label();															// op 16
};


#endif