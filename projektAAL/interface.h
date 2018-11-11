/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#ifndef PROJEKTAAL_INTERFACE_H
#define PROJEKTAAL_INTERFACE_H

#include <fstream>
#include <iostream>
#include "logic.h"
#include "graph.h"


class Interface {
public:
    Interface(int argc, char* argv[]);
    ~Interface();
    void menu(int argc, char* argv[]);

private:
    Graph *myGraph;
    Logic *logic;
    void printOptions();
    void printWaysToRunProgram();

};


#endif //PROJEKTAAL_INTERFACE_H
