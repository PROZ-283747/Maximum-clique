/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#ifndef PROJEKTAAL_INTERFACE_H
#define PROJEKTAAL_INTERFACE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <ctime>
#include "logic.h"
#include "graph.h"
#include "graphGenerator.h"


class Interface {
public:
    Interface();
    ~Interface();
    void menu(int argc, char* argv[]);

private:
    Graph *myGraph;
    Logic *logic;
    FileManager *fileManager;
    string fileWithGraph;
    int getSecondArg(char* argv[]);
    int getThirdArg(char* argv[]);
    int getFourthArg(char* argv[]);
    int getMode(char* argv[]);
    void printWaysToRunProgram();
};


#endif //PROJEKTAAL_INTERFACE_H
