#ifndef _QUADTREE_
#define _QUADTREE_

#include <sstream>
#include <iostream>
#include <set>
#include <queue>

#include "Point.hpp"
#include "Rect.hpp"
#include "QuadNode.hpp"

#define MAX_NAME_LEN 6

typedef priority_queue<QuadNode*, vector<QuadNode*>, CompareDistanceToRect> QuadNodeToRectPQ;
typedef priority_queue<QuadNode*, vector<QuadNode*>, CompareDistanceToPoint> QuadNodeToPointPQ;


const int WorldX = 0, WorldY = 0; /* coordinates of the lower left corner */
const int WorldLX = 128, WorldLY = 128;
const int MinLX = 3, MinLY = 3; /* the smallest rectangle is 3x3 */
const int MaxLX = 128, MaxLY = 128; /* the largest rectangle is 128x128 */
const int PixelLX = 1, PixelLY = 1; /* Pixel is 1x1, the smallest unit into which our quadtree will decompose the world */

enum TraversalType {
    PREORDER,
    POSTORDER
};

class QuadTree
{
private:
    QuadNode*              m_root;
    Rect*                  m_bst;
    vector<int>            m_trace;
    int                    m_width;

    /* Helpers */
    void                   start_trace();
    void                   visit(QuadNode* n);
    QuadNode*              qt_insert_helper(QuadNode* n, Rect& data);
    Rect*                  bst_insert_helper(Rect* r, Rect& data);
    void                   quad_insert(QuadNode* n, Rect& data);
    void                   search_rectangle_helper(QuadNode* curr, Rect& target, set<Rect> *results);
    void                   search_point_helper(QuadNode* curr, Point& target, Rect** result);
    bool                   delete_rectangle_helper(QuadNode* curr, Rect& target);
    bool                   collapse(QuadNode* n);
    void                   touch_helper(QuadNode* n, const Rect& target, set<Rect> *results);
    void                   within_helper(QuadNode* n, Rect& r1, Rect& r2, set<Rect> *results);
    void                   horiz_neighbor_helper(QuadNodeToRectPQ * pq, Rect& target, Rect** result);
    void                   vert_neighbor_helper(QuadNodeToRectPQ * pq, Rect& target, Rect** result);
    void                   nearest_rectangle_helper(QuadNodeToPointPQ * pq, Point& target, Rect** result);
    void                   window_helper(QuadNode* n, Rect& target, set<Rect> *results);
    void                   nearest_neighbor_helper(QuadNodeToRectPQ* pq, Rect& target, Rect** result);
    void                   lexically_greater_nearest_neighbor_helper(QuadNodeToRectPQ* pq, Rect& target, Rect** result);


public:
    QuadTree(int width);
    QuadTree();
    ~QuadTree();

    inline vector<int>     get_trace() { return m_trace; }
    inline int             get_width() { return m_width; }

    /* Traverse */
    void                   traverse(TraversalType traversal_type, void (*process) (QuadNode*));
    void                   preorder(QuadNode* n, void (*process) (QuadNode*));
    void                   postorder(QuadNode* n, void (*process) (QuadNode*));

    /* Part 3 */
    set<Rect>*             search_rectangle(Rect& target);
    bool                   insert(Rect& data);                                  // op 6
    Rect*                  search_point(Point& p);                              // op 7
    bool                   delete_rectangle(Rect& target);                      // op 8
    Rect*                  delete_point(Point& p);                              // op 8

    /* Part 4 */
    set<Rect>* 	           touch(const Rect& target);				            // op 9
    set<Rect>* 	           within(Rect& r1, Rect& r2);					        // op 10
    Rect* 	               horiz_neighbor(Rect& target);			            // op 11
    Rect* 	               vert_neighbor(Rect& target);				            // op 11
    Rect* 	               nearest_rectangle(Point& target);			        // op 12
    set<Rect>* 	           window(Rect& target);						        // op 13
    Rect* 	               nearest_neighbor(Rect& target);				        // op 14
    Rect* 	               lexically_greater_nearest_neighbor(Rect& target);	// op 15
    void 	               label();								                // op 16
};


#endif