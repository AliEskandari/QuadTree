#include <string>
#include <vector>
#include "QuadTree.hpp"
using namespace std;

/******************************************************************************
* QuadTree
******************************************************************************/
QuadTree::QuadTree(int width) : m_bst(nullptr) {

    Rect bounds = Rect(WorldX, WorldY, width, width);
    m_root = new QuadNode(bounds, 0);
    m_width = width;
}

QuadTree::QuadTree() : m_bst(nullptr), m_width(128) {

    Rect bounds = Rect(WorldX, WorldY, m_width, m_width);
    m_root = new QuadNode(bounds, 0);
}

QuadTree::~QuadTree() {
//	  delete m_root;
//    if (m_bst != nullptr) delete m_bst;
}

/******************************************************************************
* TRACE
*
* RETURN: void
*/
void QuadTree::start_trace() {

    m_trace = vector<int>();
}

void QuadTree::visit(QuadNode* n) {

    m_trace.push_back(n->m_label);
}

/******************************************************************************
* INSERT
*
* Insert rectangle in quadtree. We know rect is not already
* in tree and does not intersect any previously inserted rects.
*
* - insert into quadtree
* - insert into rectangle bst
*
* RETURN: true if data is in bounds, else false
*/
bool QuadTree::insert(Rect& data) {

    start_trace();

    if (!m_root->m_bounds.contains(data)) return false;

    m_root      = qt_insert_helper(m_root, data);
    m_bst       = bst_insert_helper(m_bst, data);

    return true;
}

QuadNode* QuadTree::qt_insert_helper(QuadNode* n, Rect& data) {

    /* if data does not enter node's bounds then return */
    if (!n->m_bounds.intersects(data)) return n;

    visit(n);

    if (n->m_type == WHITE) /* if node has space */
        /* → set data */
    {
        n->m_type = BLACK;
        n->m_rect = data;

        return n;
    }
    else if (n->m_type == BLACK) /* else if node is filled */
        /* → split node up, re-insert m_rect & insert data into quadrants */
    {
        n->split();
        n->m_type = GRAY;
        quad_insert(n, data);

        return n;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → insert data into quadrants */
    {
        quad_insert(n, data);

        return n;
    }
}

void QuadTree::quad_insert(QuadNode* n, Rect& data) {

    n->m_nw = qt_insert_helper(n->m_nw, data);
    n->m_ne = qt_insert_helper(n->m_ne, data);
    n->m_sw = qt_insert_helper(n->m_sw, data);
    n->m_se = qt_insert_helper(n->m_se, data);
}

Rect* QuadTree::bst_insert_helper(Rect* curr, Rect& data) {

    if (curr == 0)
        return &data;
    else if (data.m_name < curr->m_name)
        curr->m_left = bst_insert_helper(curr->m_left, data);
    else
        curr->m_right = bst_insert_helper(curr->m_right, data);
    return curr;
}

/*******************************************************************************
* SEARCH
*
* Search for rectangle is quadtree, and any intersecting rects
*
* RETURN: vector of intersecting rectangle ptrs, or null if none
*/
set<Rect>* QuadTree::search_rectangle(Rect& target) {

    start_trace();

    set<Rect> *results = new set<Rect>;
    search_rectangle_helper(m_root, target, results);

    if (results->size() == 0)
    {
        delete results;
        return nullptr;
    }
    else
    {
        return results;
    }
}

void QuadTree::search_rectangle_helper(QuadNode* n, Rect& target, set<Rect> *results) {

    /* return if target does not enter node's bounds */
    if (!(n->m_bounds.intersects(target))) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data intersects target, return */
    {
        if (n->m_rect.intersects(target)) results->insert(n->m_rect);
        return;
    }
    else /* (n->m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        search_rectangle_helper(n->m_nw, target, results);
        search_rectangle_helper(n->m_ne, target, results);
        search_rectangle_helper(n->m_sw, target, results);
        search_rectangle_helper(n->m_se, target, results);

        return;
    }
}

/**************************************
* Search for point in quadtree.
*
* RETURN: pointer to containing rect, or NULL if none
*/
Rect* QuadTree::search_point(Point& p) {

    start_trace();

    Rect* result = nullptr;
    search_point_helper(m_root, p, &result);

    return result;
}

void QuadTree::search_point_helper(QuadNode* n, Point& target, Rect **result) {

    /* don't consider node if target is not inside node's bounds */
    if (!n->m_bounds.contains(target)) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data intersects target, return */
    {
        if (n->m_rect.contains(target))
            *result = &(n->m_rect);
        return;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        search_point_helper(n->m_nw, target, result);
        search_point_helper(n->m_ne, target, result);
        search_point_helper(n->m_sw, target, result);
        search_point_helper(n->m_se, target, result);

        return;
    }
}

/**/
set<Rect>* QuadTree::touch(Rect& target) {

    start_trace();

    set<Rect> *results = new set<Rect>;
    touch_helper(m_root, target, results);

    if (results->size() == 0)
    {
        delete results;
        return nullptr;
    }
    else
    {
        return results;
    }
}

void QuadTree::touch_helper(QuadNode* n, Rect& target, set<Rect>* results) {

    /* return if target does not enter node's bounds */
    if (!(n->m_bounds.intersects(target))) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data touchees target, return */
    {
        if (n->m_rect.touches(target)) results->insert(n->m_rect);
        return;
    }
    else /* (n->m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        touch_helper(n->m_nw, target, results);
        touch_helper(n->m_ne, target, results);
        touch_helper(n->m_sw, target, results);
        touch_helper(n->m_se, target, results);

        return;
    }
}

/**/
set<Rect>* QuadTree::within(Rect& r1, Rect& r2) {

    start_trace();

    set<Rect> *results = new set<Rect>;
    within_helper(m_root, r1, r2, results);

    if (results->size() == 0)
    {
        delete results;
        return nullptr;
    }
    else
    {
        return results;
    }
}

void QuadTree::within_helper(QuadNode* n, Rect& r1, Rect& r2, set<Rect>* results) {

    /* return if target does not enter node's bounds */
    if (!(n->m_bounds.intersects(r2))) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data intersects target, return */
    {
        if (n->m_rect.intersects(r2) && !n->m_rect.contains(r1)) results->insert(n->m_rect);
        return;
    }
    else /* (n->m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        within_helper(n->m_nw, r1, r2, results);
        within_helper(n->m_ne, r1, r2, results);
        within_helper(n->m_sw, r1, r2, results);
        within_helper(n->m_se, r1, r2, results);

        return;
    }
}

/**/
Rect* QuadTree::horiz_neighbor(Rect &target) {

    start_trace();

    /* create priority queue keyed on min horizontal distance to target */
    QuadNodeToRectPQ * pq = new QuadNodeToRectPQ(CompareDistanceToRect(target, HORIZONTAL));
    pq->push(m_root);

    /* find min horizontal neighbor */
    Rect* result    = nullptr;
    horiz_neighbor_helper(pq, target, &result);

    /* cleanup */
    delete pq;

    return result;
}

void QuadTree::horiz_neighbor_helper(QuadNodeToRectPQ *pq, Rect &target, Rect **result) {

    /* stop when queue is empty */
    if(pq->empty()) return;

    /* grab next node with smallest horizontal distance to target rect */
    QuadNode* n = pq->top();
    pq->pop();

    /* don't visit node if it is farther from target rect than nearest rect found so far */
    int node_to_target = n->m_bounds.horiz_distance(target);
    int result_to_target = (*result == nullptr) ? m_width : target.horiz_distance(**result);

    if (node_to_target >= result_to_target) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data is has smaller horizontal distance, return */
    {
        int rect_to_target  = n->m_rect.horiz_distance(target);

        /* if horizontal distance is valid (rects do not intersect) and less than previous min → set as result */
        if (!n->m_rect.intersects(target) && rect_to_target < result_to_target) *result = &(n->m_rect);

        return;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        pq->push(n->m_nw);
        pq->push(n->m_ne);
        pq->push(n->m_sw);
        pq->push(n->m_se);

        horiz_neighbor_helper(pq, target, result);
        horiz_neighbor_helper(pq, target, result);
        horiz_neighbor_helper(pq, target, result);
        horiz_neighbor_helper(pq, target, result);

        return;
    }
}

/**/
Rect* QuadTree::vert_neighbor(Rect &target) {

    start_trace();

    /* create priority queue keyed on min horizontal distance to target */
    QuadNodeToRectPQ * pq = new QuadNodeToRectPQ(CompareDistanceToRect(target, VERTICAL));
    pq->push(m_root);

    /* find min vertical neighbor */
    Rect* result    = nullptr;
    vert_neighbor_helper(pq, target, &result);

    /* cleanup */
    delete pq;

    return result;
}

void QuadTree::vert_neighbor_helper(QuadNodeToRectPQ * pq, Rect& target, Rect **result) {

    /* stop when queue is empty */
    if(pq->empty()) return;

    /* grab next node with smallest vertical distance to target rect */
    QuadNode* n = pq->top();
    pq->pop();

    /* don't consider node if it is farther from target rect than nearest rect found so far */
    int node_to_target = n->m_bounds.vert_distance(target);
    int result_to_target = (*result == nullptr) ? m_width : target.vert_distance(**result);

    if (node_to_target >= result_to_target) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data is has smaller vertical distance, return */
    {
        int rect_to_target  = n->m_rect.vert_distance(target);

        /* if vertical distance is valid and less than previous min set as result */
        if (!n->m_rect.intersects(target) && rect_to_target < result_to_target) *result = &(n->m_rect);

        return;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        pq->push(n->m_nw);
        pq->push(n->m_ne);
        pq->push(n->m_sw);
        pq->push(n->m_se);

        vert_neighbor_helper(pq, target, result);
        vert_neighbor_helper(pq, target, result);
        vert_neighbor_helper(pq, target, result);
        vert_neighbor_helper(pq, target, result);

        return;
    }
}

/**/
Rect* QuadTree::nearest_rectangle(Point &target) {

    start_trace();

    /* create priority queue keyed on min horizontal distance to target */
    QuadNodeToPointPQ * pq = new QuadNodeToPointPQ(CompareDistanceToPoint(target));
    pq->push(m_root);

    /* find min vertical neighbor */
    Rect* result    = nullptr;
    nearest_rectangle_helper(pq, target, &result);

    /* cleanup */
    delete pq;

    return result;
}

void QuadTree::nearest_rectangle_helper(QuadNodeToPointPQ *pq, Point &target, Rect **result) {

    /* stop when queue is empty */
    if(pq->empty()) return;

    /* grab next node with smallest distance to target */
    QuadNode* n = pq->top();
    pq->pop();

    /* don't consider node if it is farther from target than nearest rect found so far */
    int node_to_target = n->m_bounds.distance(target);
    int result_to_target = (*result == nullptr) ? m_width : (**result).distance(target);

    if (node_to_target >= result_to_target) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data is has smaller distance, return */
    {
        int rect_to_target  = n->m_rect.distance(target);

        /* if distance is less than previous min set as result */
        if (rect_to_target < result_to_target) *result = &(n->m_rect);

        return;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        pq->push(n->m_nw);
        pq->push(n->m_ne);
        pq->push(n->m_sw);
        pq->push(n->m_se);

        nearest_rectangle_helper(pq, target, result);
        nearest_rectangle_helper(pq, target, result);
        nearest_rectangle_helper(pq, target, result);
        nearest_rectangle_helper(pq, target, result);

        return;
    }
}

set<Rect>* QuadTree::window(Rect &target) {

    start_trace();

    set<Rect> *results = new set<Rect>;
    window_helper(m_root, target, results);

    if (results->size() == 0)
    {
        delete results;
        return nullptr;
    }
    else
    {
        return results;
    }
}

void QuadTree::window_helper(QuadNode *n, Rect &target, set<Rect> *results) {

    /* return if target does not enter node's bounds */
    if (!(n->m_bounds.intersects(target))) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if target contains data, return */
    {
        if (target.contains(n->m_rect)) results->insert(n->m_rect);
        return;
    }
    else /* (n->m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        window_helper(n->m_nw, target, results);
        window_helper(n->m_ne, target, results);
        window_helper(n->m_sw, target, results);
        window_helper(n->m_se, target, results);

        return;
    }

}

Rect* QuadTree::nearest_neighbor(Rect &target) {

    start_trace();

    /* create priority queue keyed on min horizontal distance to target */
    QuadNodeToRectPQ * pq = new QuadNodeToRectPQ(CompareDistanceToRect(target, DIAGONAL));
    pq->push(m_root);

    /* find min vertical neighbor */
    Rect* result    = nullptr;
    nearest_neighbor_helper(pq, target, &result);

    /* cleanup */
    delete pq;

    return result;
}

void QuadTree::nearest_neighbor_helper(QuadNodeToRectPQ* pq, Rect& target, Rect **result) {

    /* stop when queue is empty */
    if(pq->empty()) return;

    /* grab next node with smallest vertical distance to target rect */
    QuadNode* n = pq->top();
    pq->pop();

    int node_to_target = n->m_bounds.distance(target);
    int result_to_target = (*result == nullptr) ? m_width : target.distance(**result);

    /**
    *  don't consider node if:
    *  - it is farther from target rect than nearest rect found so far
    *  - target rect contains node because any rect in node will be invalid (intersects target) */
    if (target.contains(n->m_rect) || node_to_target >= result_to_target) return;

    visit(n);

    if (n->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return;
    }
    else if (n->m_type == BLACK) /* else if node has rect data */
        /* → check if data is has smaller vertical distance, return */
    {
        int rect_to_target  = n->m_rect.distance(target);

        /* if distance is valid and less than previous min set as result */
        if (!n->m_rect.intersects(target) && rect_to_target < result_to_target) *result = &(n->m_rect);

        return;
    }
    else /* (m_type == GRAY) */ /* else node is parent */
        /* → search rect in 4 quadrants */
    {
        pq->push(n->m_nw);
        pq->push(n->m_ne);
        pq->push(n->m_sw);
        pq->push(n->m_se);

        nearest_neighbor_helper(pq, target, result);
        nearest_neighbor_helper(pq, target, result);
        nearest_neighbor_helper(pq, target, result);
        nearest_neighbor_helper(pq, target, result);

        return;
    }
}

/*******************************************************************************
* DELETE
*
* Recursively searches for target rect. Once found, it is deleted
* and tree is checked for possible collapsing.
*
* Return: false if rect is not found, else true if found and deleted
* (regardless of collapsing happening)
*/
bool QuadTree::delete_rectangle(Rect& target) {

    start_trace();

    return delete_rectangle_helper(m_root, target);
}

bool QuadTree::delete_rectangle_helper(QuadNode *curr, Rect &target) {

    /* if target does not enter node's bounds → return */
    if (!curr->m_bounds.intersects(target)) return false;

    visit(curr);

    if (curr->m_type == WHITE) /* if node is empty */
        /* → return */
    {
        return false;
    }
    else if (curr->m_type == BLACK) /* else if node has rect data */
        /* → check if data == target, delete rect */
    {
        if (curr->m_rect == target)
        {
            curr->m_type = WHITE;
            return true;
        }
    }
    else /* (curr->m_type == GRAY) */ /* else node is parent */
        /* →  look through 4 quadrants → delete, collapse */
    {
        bool did_delete_nw = delete_rectangle_helper(curr->m_nw, target);
        bool did_delete_ne = delete_rectangle_helper(curr->m_ne, target);
        bool did_delete_sw = delete_rectangle_helper(curr->m_sw, target);
        bool did_delete_se = delete_rectangle_helper(curr->m_se, target);

        return (did_delete_nw || did_delete_ne || did_delete_sw || did_delete_se
        ) ? collapse(curr) : false;
    }

    return false;
}

bool QuadTree::collapse(QuadNode* parent) {

    /* quadrants are either white or black & at least one is black */
    QuadNode *quadrants[4] = {parent->m_nw, parent->m_ne, parent->m_sw, parent->m_se};

    /* look for common rect in all 4 quads */
    Rect *common = nullptr;
    for (int i = 0; i < 4; ++i) {
        if (quadrants[i]->m_type == BLACK) {
            if (common == nullptr) common = &(quadrants[i]->m_rect);
            else if (*common != quadrants[i]->m_rect) return true;
        }
    }

    /* found common rect → collapse */
    parent->m_type = BLACK;
    parent->m_rect = *common;

    /* clean up quadrants */
    delete parent->m_nw;
    delete parent->m_ne;
    delete parent->m_sw;
    delete parent->m_se;

    parent->m_nw = nullptr;
    parent->m_ne = nullptr;
    parent->m_sw = nullptr;
    parent->m_se = nullptr;

    return true;
}

/**************************************
* Delete rectangle that contains the given point. First find rectangle, then
* delete it using delete_rectangle.
*
* Return: ptr to deleted rect if found and deleted, nullptr if not found
*/
Rect* QuadTree::delete_point(Point& p) {

    Rect* found = search_point(p);

    if (found)
    {
        delete_rectangle(*found);
        return found;
    }
    else
    {
        return nullptr;
    }
}

/*******************************************************************************
**
* TRAVERSE
*/
void QuadTree::traverse(TraversalType traversal_type, void (*process)(QuadNode*)) {

    if (traversal_type == PREORDER) preorder(m_root, process);
    else if (traversal_type == POSTORDER) postorder(m_root, process);
}

void QuadTree::preorder(QuadNode* n, void (*process) (QuadNode*)) {

    if (n == nullptr) return;

    process(n);
    preorder(n->m_nw, process);
    preorder(n->m_ne, process);
    preorder(n->m_sw, process);
    preorder(n->m_se, process);
}

void QuadTree::postorder(QuadNode* n, void (*process) (QuadNode*)) {

    if (n == nullptr) return;

    preorder(n->m_nw, process);
    preorder(n->m_ne, process);
    preorder(n->m_sw, process);
    preorder(n->m_se, process);
    process(n);
}