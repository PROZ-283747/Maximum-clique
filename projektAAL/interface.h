/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
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
#include "heuristicAlg.h"


class Interface {
public:
    Interface();
    ~Interface();
    void menu(int argc, char* argv[]);

private:
    Graph *myGraph;
    Logic2 *logic;
    HeuristicAlg *heurAlg;
    FileManager *fileManager;
    int getSecondArg(char* argv[]);
    int getThirdArg(char* argv[]);
    int getFourthArg(char* argv[]);
    int getFifthArg(char* argv[]);
    int getSixthArg(char* argv[]);
    int getMode(char* argv[]);
    void printWaysToRunProgram();
};


#endif //PROJEKTAAL_INTERFACE_H
