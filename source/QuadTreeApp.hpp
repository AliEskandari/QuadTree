#ifndef _QUADTREEAPP_
#define _QUADTREEAPP_

#include <string>
#include <vector>
#include <map>
#include "QuadTree.hpp"

#define ON true
#define OFF false

class Message
{
private:
    bool        m_succ;
    string      m_trace;
    string      m_output;
    string      m_extra;
public:
    Message(bool succ, string trace, string output, string extra) : m_succ(succ), m_trace(trace), m_output(output), m_extra(extra) {}
    Message(bool succ, string trace, string output) : m_succ(succ), m_trace(trace), m_output(output), m_extra("") {}

    Message() : m_succ(false), m_trace(""), m_output(""), m_extra("") {}

    inline bool         is_succ() { return m_succ; };
    inline string       get_trace() { return m_trace; };
    inline string       get_output() { return m_output; };
    inline string       get_extra() { return m_extra; };
};

class QuadTreeApp
{
private:
    QuadTree                        m_quadtree;
    map<string, Rect>               m_rect_list;
    bool                            m_should_trace;

public:
    QuadTreeApp();
    ~QuadTreeApp();

    /* Display Helpers */
    static void display_quadrants(QuadNode* n);
    static void display_rects(QuadNode* n);

    /* Trace */
    inline bool should_trace() { return m_should_trace; }
    Message*    set_trace(bool on_off);

    /* Part 3 */
    Message* init_quadtree(int width);											// op 1
    Message* display();															// op 2
    Message* list_rectangles();													// op 3
    Message* create_rectangle(string name, int x, int y, int w, int h);		    // op 4
    Message* create_rectangle_random(string name);								// op 4
    Message* search_rectangle(string name); 									// op 5

    Message* move(string name, int cx, int cy);									// ?
    Message* insert(string name);												// op 6
    Message* search_point(int x, int y);						                // op 7
    Message* delete_rectangle(string name);										// op 8
    Message* delete_point(int x, int y);		        					    // op 8

    /* Part 4 */
    void touch(string name);					    							// op 9
    void within(string name, int dist);							    			// op 10
    void horiz_neighbor(string name);						    				// op 11
    void vert_neighbor(string name);						    				// op 11
    void nearest_rectangle(int x, int y);					    				// op 12
    void window(int x1, int x2, int y1, int y2);			    				// op 13
    void nearest_neighbor(string name);						    				// op 14
    void lexically_greater_nearest_neighbor(string name);	    				// op 15
    void label();											    				// op 16
};


#endif