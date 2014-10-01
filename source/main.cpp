/*
 * main.cpp
 *
 *  Created on: Sep 14, 2014
 *      Author: Ali
 */

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#include "QuadTreeApp.hpp"

bool print_op(int num, vector<string> cmd, int len);

int main()
{
    QuadTreeApp q;

    char line[256];
    char *pch;
    vector<string> cmd;
    string op;

	do {
        // get line from stdin
        cin.getline(line, 50); // TODO: check to see if line data is erased when reusing
        cmd.clear();

        // split line into tokens
        pch = strtok(line, " (,)");
        while (pch != NULL) {
            cmd.push_back(pch);
            pch = strtok(NULL, "(,)");
        }

        // grab operation token -> set uppercase
        op = cmd[0];
        transform(op.begin(), op.end(), op.begin(), ::toupper);

        // execute corresponding operation
        if (op == "INIT_QUADTREE") {
            if (print_op(1, cmd, 1))
                q.init_quadtree(stoi(cmd[1]));
        } else if (op == "DISPLAY") {
            if (print_op(2, cmd, 0))
                q.display();
        } else if (op == "LIST_RECTANGLES") {
            if (print_op(3, cmd, 0))
                q.list_rectangles();
        } else if (op == "CREATE_RECTANGLE") {
            if (print_op(4, cmd, 5))
                q.create_rectangle(cmd[1], stoi(cmd[2]), stoi(cmd[3]), stoi(cmd[4]), stoi(cmd[5]));
        } else if (op == "CREATE_RECTANGLE_RANDOM") {
            if (print_op(4, cmd, 1))
                q.create_rectangle_random(cmd[1]);
        } else if (op == "RECTANGLE_SEARCH") {
            if (print_op(5, cmd, 1))
                q.rectangle_search(cmd[1]);
        } else if (op == "INSERT") {
            if (print_op(6, cmd, 1))
                q.insert(cmd[1]);
        } else if (op == "SEARCH_POINT") {
            if (print_op(7, cmd, 2))
                q.search_point(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "DELETE_RECTANGLE") {
            if (print_op(8, cmd, 1))
                q.delete_rectangle(cmd[1]);
        } else if (op == "DELETE_POINT") {
            if (print_op(8, cmd, 2))
                q.delete_point(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "MOVE") {
            if (print_op(9, cmd, 2))
                q.move(cmd[1], stoi(cmd[2]), stoi(cmd[3]));
        } else if (op == "TOUCH") {
            if (print_op(10, cmd, 1))
                q.touch(cmd[1]);
        } else if (op == "WITHIN") {
            if (print_op(11, cmd, 2))
                q.within(cmd[1], stoi(cmd[2]));
        } else if (op == "HORIZ_NEIGHBOR") {
            if (print_op(12, cmd, 1))
                q.horiz_neighbor(cmd[1]);
        } else if (op == "VERT_NEIGHBOR") {
            if (print_op(12, cmd, 1))
                q.vert_neighbor(cmd[1]);
        } else if (op == "NEAREST_RECTANGLE") {
            if (print_op(13, cmd, 2))
                q.nearest_rectangle(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "WINDOW") {
            if (print_op(14, cmd, 4))
               q.window(stoi(cmd[1]), stoi(cmd[2]), stoi(cmd[3]), stoi(cmd[4]));
        } else if (op == "NEAREST_NEIGHBOR") {
            if (print_op(15, cmd, 1))
                q.nearest_neighbor(cmd[1]);
        } else if (op == "LEXICALLY_GREATER_NEAREST_NEIGHBOR") {
            if (print_op(16, cmd, 1))
                q.lexically_greater_nearest_neighbor(cmd[1]);
        } else if (op == "LABEL") {
            if (print_op(17, cmd, 0))
                q.label();
        } else if (op == "TRACE"){
//            transform(cmd[1].begin(), cmd[1].end(), cmd[1].begin(), ::toupper);
//            if (cmd[1] == "ON") cout << "TRACE IS ON" << endl;
//            else if (cmd[1] == "OFF") cout << "TRACE IS OFF" << endl;
//            else cout << "INVALID TRACE COMMAND" << endl;
        } else if (op == "QUIT") {
            cout << "SESSION ENDED" << endl;
        } else{
            cout << "PLEASE ENTER A VALID COMMAND" << endl;
        }
	} // QUIT exits the program
    while (op != "QUIT");
	
    return 0;
}

bool print_op(int num, vector<string> cmd, int len) {
    if (cmd.size() - 1 != len) {
        cout << "INCORRECT NUMBER OF PARAMETERS" << endl;
        return false;
    } else {
        cout << num;
        for (int i = 1; i <= len; i++) {
            cout << " ";
            cout << cmd[i];
        }
        cout << endl;
        return true;
    }
}

