/* 1st November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include "interface.h"
#include "graph.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(){
    Interface *interface = new Interface();
    interface->menu();

    delete interface;
    return 0;
}
