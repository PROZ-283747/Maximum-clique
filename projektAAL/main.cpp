/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include "interface.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

    Interface *interface = new Interface();
    interface->menu(argc, argv);

    delete interface;
    return 0;
}
