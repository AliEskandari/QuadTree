/*
 * main.cpp
 *
 *  Created on: Sep 14, 2014
 *      Author: Ali
 */

#include <iostream>
#include <vector>
#include <cstring>
#include "QuadTreeApp.hpp"
using namespace std;

#define MAX_STRING_LEN 256

bool is_valid_op(int num, vector<string> cmd, unsigned int len);
void produce_output(Message* message, vector<string>& cmd);

int main()
{
    QuadTreeApp     q;
    Message*        message = nullptr;

    bool            debug = false;

    char            line[256];
    char*           pch;
    vector<string>  cmd;
    string          op;


    if (debug) {
//        q.set_trace(ON);
//        produce_output(q.init_quadtree(8), cmd);
//        produce_output(q.list_rectangles(), cmd);
//        produce_output(q.create_rectangle("R1", 5, 5, 25, 25), cmd);
//        produce_output(q.create_rectangle("R4", 200, 200, 210, 210), cmd);
//        produce_output(q.create_rectangle("R2", 20, 20, 31, 31), cmd);
//        produce_output(q.create_rectangle("R3", 30, 30, 40, 40), cmd);
//        produce_output(q.insert("R4"), cmd);
//        produce_output(q.search_point(1, 1), cmd);
//        produce_output(q.insert("R1"), cmd);
//        produce_output(q.insert("R4"), cmd);
//        produce_output(q.insert("R2"), cmd);
//        produce_output(q.search_point(1, 1), cmd);
//        produce_output(q.insert("R3"), cmd);
//        produce_output(q.search_point(5, 5), cmd);
//        produce_output(q.list_rectangles(), cmd);
//        produce_output(q.search_rectangle("R2"), cmd);
//        produce_output(q.search_point(1, 1), cmd);
//        produce_output(q.insert("R2"), cmd);
//        produce_output(q.search_point(7, 7), cmd);
//        produce_output(q.insert("R2"), cmd);
//        produce_output(q.delete_point(10, 10), cmd);

        produce_output(q.init_quadtree(8), cmd);
        produce_output(q.create_rectangle("R1",5,5,25,25), cmd);
        produce_output(q.create_rectangle("R2",20,20,31,31), cmd);
        produce_output(q.create_rectangle("R3",30,30,40,40), cmd);
        produce_output(q.create_rectangle("R4",200,200,210,210), cmd);
        produce_output(q.create_rectangle("S1",5,5,10,10), cmd);
        produce_output(q.create_rectangle("S2",10,10,13,13), cmd);
        produce_output(q.create_rectangle("S3",14,14,20,20), cmd);
        produce_output(q.create_rectangle("S4",13,2,14,24), cmd);
        produce_output(q.insert("R3"), cmd);
        produce_output(q.insert("R4"), cmd);
        produce_output(q.insert("S1"), cmd);
        produce_output(q.insert("S3"), cmd);
        produce_output(q.horiz_neighbor("R2"), cmd);

        return 0;
    }


    do {
        /* get line from stdin */
        cin.getline(line, MAX_STRING_LEN); // TODO: check to see if line data is erased when reusing
        if (cin.eof()) return 0;
        cmd.clear();

        /* split line into tokens */
        pch = strtok(line, " (,)");
        while (pch != NULL) {
            cmd.push_back(pch);
            pch = strtok(NULL, "(,)");
        }

        /* grab operation token -> set uppercase */
        op = cmd[0];
        transform(op.begin(), op.end(), op.begin(), ::toupper);

        /* execute corresponding operation */
        if (op == "INIT_QUADTREE") {
            if (is_valid_op(1, cmd, 1))
                message = q.init_quadtree(stoi(cmd[1]));
        } else if (op == "DISPLAY") {
            if (is_valid_op(2, cmd, 0))
                message = q.display();
        } else if (op == "LIST_RECTANGLES") {
            if (is_valid_op(3, cmd, 0))
                message = q.list_rectangles();
        } else if (op == "CREATE_RECTANGLE") {
            if (is_valid_op(4, cmd, 5))
                message = q.create_rectangle(cmd[1], stoi(cmd[2]), stoi(cmd[3]), stoi(cmd[4]), stoi(cmd[5]));
        } else if (op == "CREATE_RECTANGLE_RANDOM") {
            if (is_valid_op(4, cmd, 1))
                message = q.create_rectangle_random(cmd[1]);
        } else if (op == "RECTANGLE_SEARCH") {
            if (is_valid_op(5, cmd, 1))
                message = q.search_rectangle(cmd[1]);
        } else if (op == "INSERT") {
            if (is_valid_op(6, cmd, 1))
                message = q.insert(cmd[1]);
        } else if (op == "SEARCH_POINT") {
            if (is_valid_op(7, cmd, 2))
                message = q.search_point(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "DELETE_RECTANGLE") {
            if (is_valid_op(8, cmd, 1))
                message = q.delete_rectangle(cmd[1]);
        } else if (op == "DELETE_POINT") {
            if (is_valid_op(8, cmd, 2))
                message = q.delete_point(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "MOVE") {
            if (is_valid_op(9, cmd, 2))
                message = q.move(cmd[1], stoi(cmd[2]), stoi(cmd[3]));
        } else if (op == "TOUCH") {
            if (is_valid_op(10, cmd, 1))
                message = q.touch(cmd[1]);
        } else if (op == "WITHIN") {
            if (is_valid_op(11, cmd, 2))
                message = q.within(cmd[1], stoi(cmd[2]));
        } else if (op == "HORIZ_NEIGHBOR") {
            if (is_valid_op(12, cmd, 1))
                message = q.horiz_neighbor(cmd[1]);
        } else if (op == "VERT_NEIGHBOR") {
            if (is_valid_op(12, cmd, 1))
                message = q.vert_neighbor(cmd[1]);
        } else if (op == "NEAREST_RECTANGLE") {
            if (is_valid_op(13, cmd, 2))
                q.nearest_rectangle(stoi(cmd[1]), stoi(cmd[2]));
        } else if (op == "WINDOW") {
            if (is_valid_op(14, cmd, 4))
                q.window(stoi(cmd[1]), stoi(cmd[2]), stoi(cmd[3]), stoi(cmd[4]));
        } else if (op == "NEAREST_NEIGHBOR") {
            if (is_valid_op(15, cmd, 1))
                q.nearest_neighbor(cmd[1]);
        } else if (op == "LEXICALLY_GREATER_NEAREST_NEIGHBOR") {
            if (is_valid_op(16, cmd, 1))
                q.lexically_greater_nearest_neighbor(cmd[1]);
        } else if (op == "LABEL") {
            if (is_valid_op(17, cmd, 0))
                q.label();
        } else if (op == "TRACE") {
            transform(cmd[1].begin(), cmd[1].end(), cmd[1].begin(), ::toupper);
            if (cmd[1] == "ON" || cmd[1] == "OFF") message = q.set_trace(cmd[1] == "ON" ? ON : OFF);
            else cout << "INVALID TRACE COMMAND" << endl;
        } else if (op == "GET_STATE") {
            message = q.get_state();
        } else if (op == "QUIT") {
            cout << "SESSION ENDED" << endl;
        } else {
            cout << "PLEASE ENTER A VALID COMMAND" << endl;
        }

        produce_output(message, cmd);
        delete message;
        message = nullptr;

	} /* QUIT exits the program */
    while (op != "QUIT");
	
    return 0;
}


bool is_valid_op(int num, vector<string> cmd, unsigned int len) {
    
    if (cmd.size() - 1 != len) {
        cout << "INCORRECT NUMBER OF PARAMETERS" << endl;
        return false;
    } else {
        return true;
    }
}

/**
* Print operation, args, and message
*
* OPERATION(ARG1, ..., ARGN) [NODE1 NODE2 .... ]: MESSAGE
*/
void produce_output(Message* message, vector<string>& cmd) {

    if (message != nullptr) {

        if (cmd.size() != (unsigned int) 0) {
            /* print: OP(ARG1, ARG2, ...) */
            cout << cmd[0] << "(";
            for (unsigned int i = 1; i < cmd.size(); i++) {
                cout << cmd[i];
                if (i != cmd.size() - 1) cout << ", ";
            }
            cout << ")";
        }

        /* print trace: [NODE1 NODE2 NODE3 ...] */
        if (message->get_trace() != "") cout << " " + message->get_trace() << " ";

        /* print op output */
        cout << ": " + message->get_output() << endl;
    }
}


