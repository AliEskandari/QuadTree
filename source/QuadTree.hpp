#ifndef _QUADTREE_
#define _QUADTREE_

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 256
#define MAX_NAME_LEN 6

const int WorldX = 0, WorldY = 0; /* coordinates of the lower left corner*/
const int WorldLX = 128, WorldLY = 128;
const int MinLX = 3, MinLY = 3; /* the smallest rectangle is 3x3 */

const int MaxLX = 128, MaxLY = 128; /* the largest rectangle is 128x128 */
const int PixelLX = 1, PixelLY = 1; /* Pixel is 1x1, the smallest unit into which our quadtree will decompose the world */

typedef enum {LEFT, RIGHT} Direction;
typedef enum {NW, NE, SW, SE} Quadrant;
typedef enum {GRAY, BLACK, WHITE} Nodetype;

class Point
{
public:
    Point(int x, int y);
    Point();
    ~Point();

	int m_x;
    int m_y;
};

class Rect 
{
public:
    Rect(std::string r, int x1, int x2, int y1, int y2);
    Rect();
    ~Rect();

	std::string    m_name;                 /* name of rectangle */
	Point          m_corner;               /* lower left corner */
	Point          m_size;                 /* horizontal and vertical size */
	int            m_label;                /* user for op #11: LABEL() */
	Rect*          m_son[2];                  /* left and right sons */
};



class QuadTree
{
private:
    class QuadNode
    {
    public:
        QuadNode(Rect& data, Point pt, Quadrant quadrant);
        QuadNode();
        ~QuadNode();

        Nodetype    m_type;                        /* GRAY, BLACK, WHITE */
        Rect        m_data;                        /* pointer to rectangle, contained in this quadrant */
        QuadNode*   m_son[4];                         /* four principle quadrant directions */
        Point		m_pt;
        Quadrant	m_quadrant;

    };


	QuadNode*  m_root;
	Rect*      m_rect;
    int        m_width;

    QuadNode* insert(QuadNode* root, Rect data);
public:
	QuadTree(int width);
	QuadTree();
	~QuadTree();

	/* Part 3 */
	void rectangle_search(std::string r);           // op 5
    void move(std::string r, int cx, int cy);       // ? 
    void insert(Rect data);                         // op 6
    void search_point(int x, int y);                // op 7
    void delete_rectangle(std::string r);           // op 8
    void delete_point(int x, int y);                // op 8

	/* Part 4 */
	void 	touch();								// op 9
	void 	within();								// op 10
	void 	horiz_neighbor();						// op 11
	void 	vert_neighbor();						// ...
	void 	nearest_rectangle();					// op 12
	void 	window();								// op 13
	void 	nearest_neighbor();						// op 14
	void 	lexically_greater_nearest_neighbor();	// op 15
	void 	label();								// op 16
};


#endif
