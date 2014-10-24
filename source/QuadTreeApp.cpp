#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <cstring>
#include "drawing/drawing.c"
#include "QuadTreeApp.hpp"
using namespace std;

string to_string(vector<int> trace) {

    vector<int>::iterator i;
    string result = "[";

    for (i = trace.begin(); i != trace.end(); i++) {
        result += to_string(*i);
        if (i != trace.end() - 1) result += " ";
    }
    result += "]";

    return result;
}

/******************************************************************************
* QuadTreeApp
*****************************************************************************/
QuadTreeApp::QuadTreeApp() : m_should_trace(false) {
}

QuadTreeApp::~QuadTreeApp() {
}

/**********************************************************
* Functions
**********************************************************/
Message* QuadTreeApp::get_state() {

    string output = "\nproduce_output(q.init_quadtree(" + to_string((int)pow(m_quadtree.get_width(),.5)) + "), cmd);";

    /* print all rectangles in m_rect_list */
    map<string, Rect>::iterator i;
    Rect* r;

    /* produce_output(q.create_rectangle("R3", 30, 30, 40, 40), cmd); */
    for(i = m_rect_list.begin(); i != m_rect_list.end(); i++) {
        r = &i->second;

        output += "\nproduce_output(q.create_rectangle(";
        output += "\""+ i->first + "\",";
        output += to_string(r->m_x1) + "," + to_string(r->m_y1) + ",";
        output += to_string(r->m_x2) + "," + to_string(r->m_y2) + "), cmd);";
    }

    /* print all rectangles in m_active_rects */
    set<Rect>::iterator j;

    /* produce_output(q.insert("R3"), cmd); */
    for(j = m_active_rects.begin(); j != m_active_rects.end(); j++) {
        output += "\nproduce_output(q.insert(";
        output += "\""+ (*j).m_name + "\"), cmd);";
    }

    return new Message(true, "", output);
}

/**************************************
* TRACE
*
* Set trace on. Lists the nodes (both leaf and nonleaf) that have been visited
* while executing the operation. This trace is initiated by the command TRACE ON
* and is terminated by the command TRACE OFF.
*/
Message* QuadTreeApp::set_trace(bool on_off) {

    m_should_trace = on_off;
    string on_off_str = (on_off) ? "on" : "off";

    return new Message(
            true,
            "",
            "trace is " + on_off_str
    );
}

/**************************************
* INIT_QUADTREE(int w):                                                                            (OPCODE = 1)
*
* Initialize a new empty quad-tree T that covers the area from (0,0) to (2^w,2^w).
* Any existing quad-tree should be deleted. Print the message
* “initialized a quadtree of width D” where D is 2^w.
*
* As a default, you should assume w = 7, i.e., a size of 128 × 128.
* The pixel at the lower left corner has coordinate values (0,0) and
* the pixel at the upper right corner has coordinate values (2w − 1,2w − 1).
*/
Message* QuadTreeApp::init_quadtree(int w) {

    int width = (int) pow(2, w);

    /* return error if tree is too small (< 3x3) */
    if (width < MinLX)
    {
        return new Message(
                false,
                "",
                "tree width is too small"
        );
    }

    /* init */
    m_quadtree = QuadTree(width);

    /* message */
    return new Message(
            true,
            "",
            "initialized a quadtree of width " + to_string(width)
    );
}

/**************************************
* TODO: Test
* DISPLAY() :                                                                                      (OPCODE = 2)
*
* RETURN: void
*/
Message* QuadTreeApp::display() {

    StartPicture(m_quadtree.get_width(), m_quadtree.get_width());

    /* process nodes to produce display commands
     * (seperated traverses to produce rect commands on top of quadrants) */
    m_quadtree.traverse(PREORDER, display_quadrants);
    m_quadtree.traverse(PREORDER, display_rects);

    EndPicture();

    return nullptr;
}

void QuadTreeApp::display_quadrants(QuadNode* n) {

    if (n->m_type == WHITE) /* leaf node, no rect */
    {
        /* do nothing */
    }
    else if (n->m_type == GRAY) /* internal node */
        /* → draw node's quadrants w/ dashed lines */
    {
        /* set dash line */
        SetLineDash(2, 2);

        /* get bounds and points */
        Rect bounds = n->m_bounds;
        int lx      = bounds.m_x1;       /* left x */
        int by      = bounds.m_y1;       /* top y */
        int rx      = lx + bounds.m_x2;  /* right x */
        int ty      = by + bounds.m_y2;  /* top y */

        /* draw quadrant lines */
        DrawLine((rx - lx)/2, by, (rx - lx)/2, ty); /* y-axis */
        DrawLine(lx, (ty - by)/2, rx, (ty - by)/2); /* x-axis */
    }
    else /* (n->m_type == BLACK) */ /* node has rect */
    {
        /* do nothing */
    }
}

void QuadTreeApp::display_rects(QuadNode* n) {

    if (n->m_type == WHITE) /* leaf node, no rect */
    {
        /* do nothing */
    }
    else if (n->m_type == GRAY) /* internal node */
    {
        /* do nothing */
    }
    else /* (n->m_type == BLACK) */ /* node has rect */
    {
        /* set solid line for rects */
        SetLineDash(1, 0);

        /* draw rect */
        Rect rect = n->m_rect;
        DrawRect(rect.m_x1, rect.m_y2, rect.m_x2, rect.m_y1);

        /* draw name at center of rect */
        char name[MAX_NAME_LEN + 1];
        strcpy(name, rect.m_name.c_str());
        DrawName(name, rect.m_x1 + rect.m_w/2, rect.m_y1 + rect.m_h/2);
    }
}

/**************************************
* LIST_RECTANGLES() :                                                                              (OPCODE = 3)
*
* Print the message “listing N rectangles: ” where N is the total number of
* rectangles in C. Then, starting from the next line, print a list of all
* the rectangles in the collection C in the ascending order of their names.
* Print each rectangle in one line. For each rectangle print its name,
* its lower left x and y coordinate values and its upper right x and y coordinate
* values in order and separate them by spaces.
*/
Message* QuadTreeApp::list_rectangles() {

    /* listing N rectangles */
    string output = "listing " + to_string(m_rect_list.size()) + " rectangles:";

    /* print all rectangles in m_rect_list */
    map<string, Rect>::iterator i;
    Rect* r;

    for(i = m_rect_list.begin(); i != m_rect_list.end(); i++) {
        r = &i->second;

        output += "\n" + i->first + " ";
        output += to_string(r->m_x1) + " " + to_string(r->m_y1) + " ";
        output += to_string(r->m_x2) + " " + to_string(r->m_y2);
    }

    return new Message(true, "", output);
}

/**************************************
* CREATE_RECTANGLE(string R, int x, int y, int w, int h) :                                         (OPCODE = 4)
*
* Create a new rectangle with the name R and lower left corner at (x, y) and
* upper right corner at (x + w, y + h) and add it to the collection C. Note that
* the rectangle does not need to be within the valid range of the rectangle tree T.
* Print the message “created rectangle R” where R is the name of the rectangle.
*
* Must be bigger than 3x3 and smaller than 128x128
*/
Message* QuadTreeApp::create_rectangle(string r, int llx, int lly, int urx, int ury) {

    int w = urx - llx;
    int h = ury - lly;

    /* check if name is too long */
    if (r.length() > MAX_NAME_LEN) return new Message(false, "", "rectangle name is too long");

    /* check if rect is too small */
    if (w < MinLX && h < MinLY) return new Message(false, "", "rectangle is too small");

    /* create and add rectangle to rect_list */
    Rect rect = Rect(r, llx, lly, urx, ury);
    m_rect_list[r] = rect;

    return new Message(true, "", "created rectangle " + r);
}

/**************************************
* CREATE_RECTANGLE_RANDOM(string R) :                                                              (OPCODE = 4)
*
* Create a new rectangle with the name R and random coordinate values and add it to C.
* Print the message “created rectangle R X Y W H” where R is the name of the
* rectangle and (X,Y) and (X+W, Y+H) are the coordinate values of its lower left
* corner and upper right corner, respectively.
*/
Message* QuadTreeApp::create_rectangle_random(string r) {

    /* init random seed */
    srand(time(NULL));

    int tree_width = m_quadtree.get_width();

    Rect rand_rect = Rect(
            r,
            rand() % (tree_width - 1),
            rand() % (tree_width - 1),
            rand() % (tree_width - 1) + 1,
            rand() % (tree_width - 1) + 1
    );

    m_rect_list[r] = rand_rect;

    return new Message(
            true,
            "",
            "created random rectangle " +
                    r + " " +
                    to_string(rand_rect.m_x1) + " " +
                    to_string(rand_rect.m_y1) + " " +
                    to_string(rand_rect.m_x2) + " " +
                    to_string(rand_rect.m_y2)
    );
}

/**************************************
* TODO: Find a way to return intersecting rects in order of finding them, with no dups
* RECTANGLE_SEARCH(string R) :                                                                     (OPCODE = 5)
*
* Search for all the rectangles in T that intersect with the rectangle R.
* Print the message “found N rectangles: R1 R2 ... ” where N is the number of rectangles
* in T that intersect R. and R1, R2, . . . are the names of those rectangles.
* If R itself is in T then it should be printed as well. You should
* print the intersecting rectangles in the order they were visited first.
* You should traverse the quadtree in the order of NW, NE, SW, SE to visit/print
* the rectangles in the correct order. You should avoid visiting quadtree nodes
* that do not intersect with R.
*
* - Grab rectangle from collection
* - search for rectangle and any intersecting rects in tree
* - If no results: not in tree
* - else: print all intersecting rectangles
*/
Message* QuadTreeApp::search_rectangle(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target = m_rect_list.find(r)->second;

    /* search tree */
    set<Rect> *results = nullptr;
    results = m_quadtree.search_rectangle(target);

    /* output results */
    if (results != nullptr)
    {
        string output = "found " + to_string(results->size()) + " rectangles:";

        set<Rect>::iterator i;
        for (i = results->begin(); i != results->end(); i++) output += " " + (*i).m_name;

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                output,
                (*results->begin()).m_name /* extra: intersecting rect name */
        );
    }
    else
    {
        return new Message(
                false,
                "",
                r + " does not intersect an existing rectangle"
        );
    }
}

/**************************************
* MOVE(string N, int CX, int CY) :                                                                 (OPCODE = ?)
*
* Move a rectangle in the Rectangle quadtree. The command is invoked by MOVE(N,CX,CY) where N is
* the name of the rectangle, CX, CY are the translation of the centroid of N
* across the x and y coordinate axes, and they must be integers.
* The command returns N if it was successful in moving the specified rectangle
* and outputs a message indicating it. Otherwise, output appropriate error messages if N
* was not found in the Rectangle quadtree, or if after the operation N lies outside
* the space spanned by the Rectangle quadtree. Note that the successful execution
* of the operation requires that the moved rectangle does not overlap any of the
* existing rectangles in which case an appropriate error message is emitted.
*/
Message* QuadTreeApp::move(string r, int cx, int cy) {

    /* delete rect from tree */
    Message* delete_m   = delete_rectangle(r);

    if (delete_m->is_succ()) /* rect found and deleted from tree*/
    {
        delete delete_m;

        /* remove rect from collection */
        Rect rect_to_move  = m_rect_list.find(r)->second;
        m_rect_list.erase(r);

        /* create new "moved" rect */
        Message* create_m  = create_rectangle(
                r,
                rect_to_move.m_x1 +cx,
                rect_to_move.m_y1 +cy,
                rect_to_move.m_x2,
                rect_to_move.m_y2
        );

        if (create_m->is_succ()) /* rect created successfully, is within bounds */
            /* → insert newly created "moved" rect */
        {
            delete create_m;

            /* insert moved rect */
            Message* insert_m =  insert(r);

            if (insert_m->is_succ())
            {
                delete insert_m;

                return new Message(
                        true,
                        "",
                        "moved rect " + r + " to " +
                                to_string(rect_to_move.m_x1 +cx) + " " +
                                to_string(rect_to_move.m_y1 +cy) + " " +
                                to_string(rect_to_move.m_x2) + " " +
                                to_string(rect_to_move.m_y2)
                );
            }
            else /* should not happen */
            {
                return insert_m;
            }
        }
        else /* rect not within tree bounds */
        {
            return create_m;
        }
    }
    else /* rect not found in tree or collection */
    {
        return delete_m;
    }
}

/**************************************
* INSERT(string R) :                                                                               (OPCODE = 6)
*
* Add the rectangle R to the rectangle tree T . Then print the message “inserted rectangle R”.
* If R intersects another rectangle in T or if it is already in T then print the message
* “failed: intersects with S” where S is the name of the rectangle already in T that
* would intersect with R. If the rectangle R is not entirely contained in the region covered
* by T then print the message “failed: out of range”
*
* - Grab rectangle from collection
* - check to see if rectangle is already in tree
* - if not in tree, insert
*/
Message* QuadTreeApp::insert(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(false, "", "rectangle " + r + " not found in collection");

    /* search for rect, or intersects, in tree */
    Message* search_m   = search_rectangle(r);

    if (!search_m->is_succ()) /* rect not in tree & in collection */
    {
        delete search_m;

        /* grab rect */
        Rect target = m_rect_list.find(r)->second;

        /* insert rect */
        bool succ = m_quadtree.insert(target);

        if (succ) /* rect is in bounds */
        {
            m_active_rects.insert(target);

            return new Message(
                    true,
                    (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                    "inserted rectangle " + target.m_name
            );
        }
        else /* rect not in bounds */
        {
            return new Message(
                    false,
                    "",
                    "failed: out of bounds"
            );
        }
    }
    else /* rect already in tree, or intersects */
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "failed: intersects with " + search_m->get_extra()
        );
    }
}

/**************************************
* SEARCH_POINT(int x, int y) :                                                                     (OPCODE = 7)
*
* Find the rectangle in T that contains (x,y) and print the message
* “found rectangle R” where R is the name of the rectangle. If no
* such rectangle was found then print the message “no rectangle found”.
* See Def. 1 for an explanation of when a point belongs to a rectangle.
*/
Message* QuadTreeApp::search_point(int x, int y) {

    Point p         = Point(x, y);
    Rect* result    = nullptr;

    /* search tree */
    result          = m_quadtree.search_point(p);

    /* output results */
    if (result != nullptr)
    {
        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no rectangle found"
        );
    }
}

/**************************************
* DELETE_RECTANGLE(string R) :                                                                     (OPCODE = 8)
*
* Delete the rectangle R from the quadtree T . If successful, print the
* message “deleted rectangle R” where R is the name of the rectangle being deleted.
* Note that this operation deletes the rectangle from T not from C. If the
* rectangle is in C but not in the quadtree T then print the message “rectangle not found R”.
*/
Message* QuadTreeApp::delete_rectangle(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(false, "", "rectangle " + r + " not found in collection");

    Rect target = m_rect_list.find(r)->second;

    /* delete rect */
    bool succ   = m_quadtree.delete_rectangle(target);

    if (succ) /* delete successful */
    {
        m_active_rects.erase(target);

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "deleted rectangle " + r
        );
    }
    else /* delete unsuccessful */
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "rectangle not found " + r
        );
    }

}

/**************************************
* DELETE_POINT(int x, int y) :                                                                     (OPCODE = 8)
*
* Find the rectangle in the quadtree T containing the point (x, y) and then
* delete it from the quadtree. If successful, print the message “deleted rectangle R”
* where R is the name of the rectangle being deleted. If no such rectangle was
* found then print the message “no rectangle found at (x, y)” where (x, y) is the
* coordinate values of the point. See Def. 1 for an explanation of when a point
* belongs to a rectangle.
*/
Message* QuadTreeApp::delete_point(int x, int y) {

    Point p            = Point(x, y);
    Rect* deleted_rect = m_quadtree.delete_point(p);

    if (deleted_rect != nullptr)
    {
        m_active_rects.erase(*deleted_rect);

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "deleted rectangle " + deleted_rect->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no rectangle found at (" + to_string(x) + ", " + to_string(y) + ")"
        );
    }
}

/**************************************
* TOUCH(string name) :                                                                              (OPCODE = 10)
*
* Search for all the rectangles in T that touch the rectangle R (but don’t intersect it).
* Print the message “found N rectangles: R1 R2 ... ” where N is the number of rectangles in T
* that touch R. and R1, R2, . . . are the names of those rectangles. You should print
* the touching rectangles in the order they were visited first. You should traverse
* the quadtree int the order of NW, NE, SW, SE to visit/print the rectangles in the correct order.
*/
Message* QuadTreeApp::touch(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target         = m_rect_list.find(r)->second;
    set<Rect> *results  = nullptr;

    results = m_quadtree.touch(target);

    /* output results */
    if (results != nullptr)
    {
        string output = "found " + to_string(results->size()) + " rectangles:";

        set<Rect>::iterator i;
        for (i = results->begin(); i != results->end(); i++) output += " " + (*i).m_name;

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                output,
                (*results->begin()).m_name /* extra: first touch rect name */
        );
    }
    else
    {
        return new Message(
                false,
                "",
                r + " does not touch an existing rectangle"
        );
    }
}

/******************************************************************************
* WITHIN(string R, int d) :                                                                         (OPCODE = 11)
*
* Assume that R = ((x1,y1),(x2,y2)). Define the expansion of rectangle R by distance d to be
* the rectangle R+d = ((x1 − d, y1 − d), (x2 + d, y2 + d)). Search for all the rectangles
* in T that intersect the donut shaped region contained between R and R+d. A rectangle intersects
* the region contained between R and R+d if and only if it intersects R+d and it is not
* contained in R. Print the message “found N rectangles: R1 R2 ... ” where N is the number
* of rectangles in T that intersect the region in R+d − R and R1, R2, . . . are the names of
* those rectangles.
*/
Message* QuadTreeApp::within(string r, int d) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect r1 = m_rect_list.find(r)->second;
    Rect r2 = Rect(r1.m_x1 - d, r1.m_y1 - d, r1.m_x2 + d, r1.m_y2 + d);

    set<Rect> *results = nullptr;

    results = m_quadtree.within(r1,r2);

    /* output results */
    if (results != nullptr)
    {
        string output = "found " + to_string(results->size()) + " rectangles:";

        set<Rect>::iterator i;
        for (i = results->begin(); i != results->end(); i++) output += " " + (*i).m_name;

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                output,
                (*results->begin()).m_name /* extra: first intersecting rect name */
        );
    }
    else
    {
        return new Message(
                false,
                "",
                r + "+" + to_string(d) + " - " + r + " does not intersect an existing rectangle"
        );
    }
}

/******************************************************************************
* HORIZ_NEIGHBOR(string R) :                                                                        (OPCODE = 12)
*
* Find the rectangle in the quadtree T with the minimum non-negative horizontal distance to R.
* In other words, find the rectangle in T whose projection on the X-axis is closest to
* the projection of R on the X-axis but does not intersect it. Nodes that have smaller horizontal
* distance to the query rectangle should be visited first. All the nodes with negative
* horizontal distance should be treated as having a horizontal distance of 0. If there are
* multiple nodes with the same horizontal distance then the one with a smaller node number
* should be visited first. You should avoid visiting quadtree nodes that are farther from
* the query rectangle than the nearest rectangle found so far. You should print the
* message “found rectangle S” where S is the result of the query. If no such rectangle
* was found (i.e. if the quadtree is either empty or if all the rectangle in the quadtree
* have negative horizontal distance to the query rectangle) then print the message “no rectangle found”.
*/
Message* QuadTreeApp::horiz_neighbor(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target  = m_rect_list.find(r)->second;
    Rect* result = nullptr;

    result = m_quadtree.horiz_neighbor(target);

    /* output result */
    if (result != nullptr)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                r + " does not have a horizontal neighbor"
        );
    }
}

/******************************************************************************
* VERT_NEIGHBOR(string R) :                                                                         (OPCODE = 12)
*
* Find the rectangle in the quadtree T with the minimum non-negative vertical distance to R. For a
* definition of vertical distance see Def. 5. If there are multiple rectangles that have the
* minimum non-negative vertical distance to R then choose the one that was visited first during
* the traversal of the quadtree. Traversal order and output message is similar to HORIZ_NEIGHBOR
* except that instead of horizontal distance, vertical distance should be used.
*/
Message* QuadTreeApp::vert_neighbor(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target     = m_rect_list.find(r)->second;
    Rect* result    = nullptr;

    result = m_quadtree.vert_neighbor(target);

    /* output result */
    if (result != nullptr)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                "",
                r + " does not have a vertical neighbor"
        );
    }
}

/******************************************************************************
* NEAREST_RECTANGLE(string R) :                                                                     (OPCODE = 13)
*
* Given a point, return the name of the nearest rectangle. By “nearest,” it is meant the
* rectangle whose side or corner is closest to the point. Note that this rectangle
* could also be a rectangle that contains the point. In this case, the distance is zero.
* It is invoked by the command NEAREST_RECTANGLE(PX,PY) where PX and PY are the x and y
* coordinate values, respectively, of the point. If no such rectangle exists
* (e.g., when the tree is empty), then output an appropriate message (i.e., that the tree is empty).
* If more than one rectangle is at the same distance, then return the name of just one of them.
*/
Message* QuadTreeApp::nearest_rectangle(int x, int y) {

    Point target = Point(x,y);
    Rect* result = nullptr;

    result = m_quadtree.nearest_rectangle(target);

    /* output result */
    if (result != nullptr)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no rectangle found"
        );
    }
}

/******************************************************************************
* WINDOW(int x1, int y1, int x2, int y2) :                                                          (OPCODE = 13)
*
* Search for all the rectangles in T that are entirely contained in the rectangle with lower
* left corner at (x1, y1) and upper right corner at (x2, y2). Print the message
* “found N rectangles: R1 R2 ... ” where N is the number of rectangles in T that are entirely
* within the query rectangle and R1, R2, . . . are the names of those rectangles.
* You should print the contained rectangles in the order they were visited first. You should
* traverse the quadtree in the order of NW, NE, SW, SE to visit/print the rectangles in
* the correct order.
*/
Message* QuadTreeApp::window(int x1, int y1, int x2, int y2) {

    Rect target         = Rect(x1,y1,x2,y2);
    set<Rect> *results  = nullptr;

    results = m_quadtree.window(target);

    /* output results */
    if (results != nullptr)
    {
        string output = "found " + to_string(results->size()) + " rectangles:";

        set<Rect>::iterator i;
        for (i = results->begin(); i != results->end(); i++) output += " " + (*i).m_name;

        return new Message(
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                output,
                (*results->begin()).m_name /* extra: first touch rect name */
        );
    }
    else
    {
        return new Message(
                false,
                "",
                "no rectangles found in window"
        );
    }
}

/******************************************************************************
* NEAREST_NEIGHBOR(string R) :                                                                      (OPCODE = 14)
*
* Find the rectangle in the quadtree T that is closest to R but does not intersect R.
* The distance between two rectangles is the length of the shortest line segment
* connecting them. If there are multiple rectangles that have the minimum distance
* to R then choose the one that was visited first during the traversal of the quadtree.
* Traversal order and output message is similar to HORIZ_NEIGHBOR except that instead
* of horizontal distance, the euclidian distance of the quadtree nodes to R should be used.
* If a quadtree node intersects with R then its distance to R is considered to be 0.
* Also note that you should not visit quadtree nodes that are entirely contained in R
* because they cannot possibly contain a rectangle that does not intersect with R.
*/
Message* QuadTreeApp::nearest_neighbor(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target  = m_rect_list.find(r)->second;
    Rect* result = nullptr;

    result = m_quadtree.nearest_neighbor(target);

    /* output result */
    if (result != nullptr)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no rectangle found"
        );
    }
}

/******************************************************************************
* LEXICALLY_GREATER_NEAREST_NEIGHBOR(string R) :                                                    (OPCODE = 15)
*
* This is similar to NEAREST_NEIGHBOR except that you should only consider the
* rectangles in T whose names are lexicographically greater than R. The traversal
* order and output message is also similar. Note that if there are multiple rectangles
* with the same minimum distance to R, you should choose the one that was visited first
* during the traversal of the quadtree.
*/
Message* QuadTreeApp::lexically_greater_nearest_neighbor(string r) {

    /* find rect in collection */
    if (m_rect_list.find(r) == m_rect_list.end())
        return new Message(true, "", "rectangle " + r + " not found in collection");

    Rect target  = m_rect_list.find(r)->second;
    Rect* result = nullptr;

    result = m_quadtree.lexically_greater_nearest_neighbor(target);

    /* output result */
    if (result != nullptr)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "found rectangle " + result->m_name
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no rectangle found"
        );
    }
}

/******************************************************************************
* LABEL() :                                                                                         (OPCODE = 16)
*
* You should do a connected component labeling of the rectangles in the quadtree.
* Two rectangles are considered to be connected if they are touching (either a side or a corner).
* You should then print the message “found N connected components: ” where N is the total
* number of connected components. Then, starting from the next line, print a list of all
* the rectangles in the quadtree in the ascending order of their names. For each rectangle
* print one line containing its name followed by the name of the rectangle in its connected
* component that has the lexicographically smallest name in that connected component.
*/
Message* QuadTreeApp::label() {

    set< pair<Rect,Rect> >                      touch_pairs;
    set< pair<Rect,Rect> >                      components;
    set<Rect>::const_iterator                   i;
    set<Rect>::iterator                         j;
    set< pair<Rect,Rect> >::iterator            k;
    set< pair<Rect,Rect> >::reverse_iterator    m;
    set< pair<Rect,Rect> >::iterator            l;
    map<Rect, Rect>                             smallest_connected_component;
    map<Rect,Rect>::iterator                    end = smallest_connected_component.end();
    int                                         num_connected_components = 0;

    /**
    * for each active rect:
    * - get set of directly connected rectangles
    * - add every touch pair to set of touch pairs */
    for (i = m_active_rects.begin(); i != m_active_rects.end(); i++) {

        /* get set of rectangles that i touches */
        set<Rect>* touched_rects = m_quadtree.touch(*i);

        /* for each touched rectangle, add the pair to touch_pairs */
        if (touched_rects != nullptr) {

            for (j = touched_rects->begin(); j != touched_rects->end(); j++) {

                pair<Rect,Rect> pair(*i,*j);
                touch_pairs.insert(pair);
            }
        }

        /* add touch pair of active rectangle and itself */
        pair<Rect,Rect> pair(*i,*i);
        touch_pairs.insert(pair);
    }

    /**
    * for every touch pair, given to us in sorted order b/c of set:
    * */
    for (k = touch_pairs.begin(); k != touch_pairs.end(); k++) {

        if (smallest_connected_component.find(k->first) != end)
        {
            /* do nothing */
        }
        else if (smallest_connected_component.find(k->second) != end)
            /* don't have 1st smallest connected component stored but have the second */
        {
            /* set smallest connected component of 1st to be equal to that of 2nd */
            smallest_connected_component[k->first] = smallest_connected_component[k->second];
        }
        else
            /* don't have either smallest connected components */
        {
            /* store 2nd as smallest connected component of 1st, we can do this because pairs are sorted */
            smallest_connected_component[k->first] = k->second;
            num_connected_components++;
        }
    }

    /* add new touch pairs to components in reverse in form of: (first, smallest_connected_component[first])*/
    for (m = touch_pairs.rbegin(); m != touch_pairs.rend(); m++) {

        if (smallest_connected_component.find(m->second) != end
                && smallest_connected_component[m->first] > smallest_connected_component[m->second])
        {
            smallest_connected_component[m->first] = smallest_connected_component[m->second];
            num_connected_components--;
        }

        pair<Rect,Rect> component(m->first, smallest_connected_component[m->first]);
        components.insert(component);
    }

    /* create output string */
    string output = "found " + to_string(num_connected_components) + " connected components: ";

    for (l = components.begin(); l != components.end(); l++) {

        output += "\n"+ l->first.m_name + " " + l->second.m_name;
    }

    /* output result */
    if (touch_pairs.size() != 0)
    {
        return new Message (
                true,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                output
        );
    }
    else
    {
        return new Message(
                false,
                (should_trace()) ? to_string(m_quadtree.get_trace()) : "",
                "no connected components found"
        );
    }
}
