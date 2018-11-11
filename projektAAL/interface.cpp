/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include <sstream>
#include <iterator>
#include "interface.h"

using namespace std;

Interface::Interface(int argc,  char* argv[]) {
    if(argc==2)
        myGraph = new Graph(argv[1]);
    else {
        myGraph = new Graph(argv);
    }
    logic = new Logic(myGraph);
}

Interface::~Interface() {
    delete myGraph;
    delete logic;
}

void Interface::printWaysToRunProgram() {
    cout<<"\nThis program can be used to find the biggest clique in a graph\n";
    cout<<"To run it you need to enter: \n"
        <<"1) program 1 graph.txt (if you want to read graph from file)\n"
        <<"2) program 2 dataForGraphGenerator.txt (if you want to generate graph)\n"
        <<"Specification for .txt files is in README\n\n"<<endl;
}

void Interface::menu(int argc, char* argv[]) {
    if(argc == 1 ){
        printWaysToRunProgram();
        cout << "Incorrect number of arguments ! At least 1 needed." << endl;
    }
    else {
        cout << "argc: " << argc<<endl;
        cout << "argv[1]: " << argv[1]<<endl;
            switch (argc) {
                case 2:
                    cout << "case 1" << endl;
                    myGraph->printNeighbours();
                    logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider(),logic->getSkippedNodes(), logic->getRmsize());
                    break;
                case 4:
                    cout << "Generate graph" << endl;
                    break;
                case 5:
                    cout << "Generate graph and do statistics" << endl;
                    break;
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }
        }
    }

