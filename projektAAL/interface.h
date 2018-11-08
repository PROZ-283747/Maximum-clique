//
// Created by adell.j on 01.11.2018.
//

#ifndef PROJEKTAAL_INTERFACE_H
#define PROJEKTAAL_INTERFACE_H


#include "logic.h"
#include "graph.h"

class Interface {
public:
    Interface();
    ~Interface();
    void menu();
    void printOptions();
    void readGraphFromConsole();

private:
    Graph *myGraph;
    Logic *logic;
};


#endif //PROJEKTAAL_INTERFACE_H
