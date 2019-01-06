/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */


#include "interface.h"
#include <fstream>
#include <string>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char* argv[]){

    try
    {
        Interface *interface = new Interface();
        interface->menu(argc, argv);

        interface->~Interface();
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << "\n";
    }

    return 0;
}
