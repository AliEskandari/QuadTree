QuadTree
========

CMSC420 Data Structures  Rectangle QuadTree Project

Rectangle Quadtree application allows user to enter commands that insert, delete, query, and manipulate rectangles in a quadtree data structure.

##Commands
####INIT_QUADTREE (int w)
Initialize a new empty quad-tree T that covers the area from (0,0) to (2^w,2^w). Any existing quad-tree is deleted.
####DISPLAY ()
Generates a display of a 2^WIDTH × 2^WIDTH square from the Rectangle quadtree. It is invoked by the command DISPLAY(). To draw the Rectangle quadtree, the app uses a an external drawing routine. Utilities are used to render the output of the application.
####LIST_RECTANGLES ()
Prints list of rectangles in application's rectangle collection. Rectangles listed are ones that have been successfully created with CREATE_RECTANGLE (). They are not neccessarily in the quadtree.
####CREATE_RECTANGLE (string R, int x1, int y1, int x2, int y2)
Creatse a new rectangle with the name R and lower left corner at (x1,y1) and upper right corner at (x2,y2) and added to the collection C. Note that the rectangle does not need to be within the valid range of the rectangle tree T.
####CREATE_RECTANGLE_RANDOM (string R)
Creatse a new rectangle with the name R and random coordinate values and adds it to C. Prints the message “created rectangle R X1 Y1 X2 Y2” where R is the name of the rectangle and (X1,Y1) and (X2, Y 2) are the coordinate values of its lower left corner and upper right corner, respectively.
####RECTANGLE_SEARCH (string R)
Searchs for all the rectangles in T that intersect with the rectangle R. Prints the message “found N rectangles: R1 R2 ... ” where N is the number of rectangles in T that intersect R. and R1, R2, . . . are the names of those rectangles.
If R itself is in T then it is printed as well. Intersecting rectangles are printed in the order they were visited first.
####INSERT (string R)
Adds the rectangle R to the rectangle tree T. If R intersects another rectangle in T or if it is already in T then prints the message “failed: intersects with S” where S is the name of the rectangle already in T that would intersect with R. If the rectangle R is not entirely contained in the region covered by T then prints the message “failed: out of range”
####SEARCH_POINT (int x, int y)
Finds the rectangle in T that contains (x,y) and prints the message “found rectangle R” where R is the name of the rectangle. If no such rectangle was found then prints the message “no rectangle found”.
####DELETE_RECTANGLE (string R)
Deletse the rectangle R from the quadtree T. Note that this operation deletes the rectangle from T not from C. If the rectangle is in C but not in the quadtree T then prints the message “rectangle not found R”.
####DELETE_POINT (int x, int y)
Finds the rectangle in the quadtree T containing the point (x, y) and then delete it from the quadtree. If successful, prints the message “deleted rectangle R” where R is the name of the rectangle being deleted. If no such rectangle was found then prints the message “no rectangle found at (x, y)” where (x, y) is the coordinate values of the point.
####TRACE ON and TRACE OFF
These commands enable/disable trace output. When tracing is on, app prints the node number of the quadtree nodes that were visited in the order that they were visited (pre-order) during the operation. The root of the quadtree has node number 0. Children of a quadtree node with number N are numbered as 4N +1 to 4N +4 in the order NW, NE, SW, SE. Children of a quadtree node are traversed in the order of NW, NE, SW, SE to print the node numbers is the correct order. When trace is on, the node numbers are be printed in the same line between a pair of brackets after the operation name/arguments like:
  OPERATION(ARG1, ..., ARGN) [NODE1 NODE2 .... ]: MESSAGE
Where NODE1, NODE2, ...are the node numbers for the quadtree nodes that were visited.
####TOUCH (string R)
Searches for all the rectangles in T that touch the rectangle R (but don’t intersect it).
####WITHIN (string R, int d)
Assume that R = ((x1,y1),(x2,y2)). Define the expansion of rectangle R by distance d to be the rectangle R+d = ((x1 − d, y1 − d), (x2 + d, y2 + d)). App searches for all the rectangles in T that intersect the donut shaped region contained between R and R+d.
####HORIZ_NEIGHBOR (string R)
Finds the rectangle in the quadtree T with the minimum non-negative horizontal distance to R. In other words, finds the rectangle in T whose projection on the X-axis is closest to the projection of R on the X-axis but does not intersect it. If there are multiple rectangles that have the minimum non-negative horizonal distance to R then it the one that was visited first during the traversal of the quadtree is chosen.
####VERT_NEIGHBOR (string R)
Finds the rectangle in the quadtree T with the minimum non-negative vertical distance to R. If there are multiple rectangles that have the minimum non-negative vertical distance to R then the one that was visited first during the traversal of the quadtree is chosen.
####NEAREST_RECTANGLE (int x, int y)
Finds the rectangle in the quadtree T with the minimum distance to the point (x, y). The distance of a rectangle to the point (x, y) is the length of the shortest line segment connecting the two. In particular, if the point lies on the boundary or inside a rectangle then its distance to the rectangle by the previous definition is 0. If there are multiple rectangles that have the minimum distance to (x,y) then the one that was visited first during the traversal of the quadtree is chosen.
####WINDOW (int x1, int y1, int x2, int y2)
Searchs for all the rectangles in T that are entirely contained in the rectangle with lower left corner at (x1, y1) and upper right corner at (x2, y2).
####NEAREST_NEIGHBOR (string R)
Finds the rectangle in the quadtree T that is closest to R but does not intersect R. The distance between two rectangles is the length of the shortest line segment connecting them. If there are multiple rectangles that have the minimum distance to R then the one that was visited first during the traversal of the quadtree is chosen.
####LEXICALLY_GREATER_NEAREST_NEIGHBOR (string R)
This is similar to NEAREST_NEIGHBOR except that only the rectangles in T whose names are lexicographically greater than R are considered.
####LABEL ()
Performs a connected component labeling of the rectangles in the quadtree. Two rectangles are considered to be connected if they are touching (either a side or a corner). Prints the message “found N connected components: ” where N is the total number of connected components. Then, starting from the next line, prints a list of all the rectangles in the quadtree in the ascending order of their names. For each rectangle one line is printed containing its name followed by the name of the rectangle in its connected component that has the lexicographically smallest name in that connected component.
