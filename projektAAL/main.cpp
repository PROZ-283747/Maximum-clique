/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include "interface.h"
#include <fstream>
#include <string>
#include <iostream>
#include <set>

using namespace std;
// todo:
// generowanie grafu ścieżki
// argument czy brn-Kerbosch czy heurystyka
// heurystyka
// <<in >>out
int main(int argc, char* argv[]){

    try
    {
        Interface *interface = new Interface();
        interface->menu(argc, argv);

        delete interface;
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << "\n";
    }

    return 0;
}
