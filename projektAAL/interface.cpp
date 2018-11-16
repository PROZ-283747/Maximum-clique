/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */


#include "interface.h"

using namespace std;

Interface::Interface() {
    myGraph = new Graph();
    logic = new Logic(myGraph);
}

Interface::~Interface() {
    delete myGraph;
    delete logic;
}

void Interface::printWaysToRunProgram() {
    cout<<"\nThis program can be used to find the biggest clique in a graph\n";
    cout<<"To run it you need to enter: \n"
        <<"1) program -m1 graph.txt (if you want to read graph from file)\n"
        <<"2) program -m2 -n{} -e{} -c{} (if you want to generate graph, parameters are: number od nodes, number od edges, bigest clique size)\n"
        <<"Specification for .txt files is in README\n\n"<<endl;
}

int Interface::getMode(char* argv[]){
    char *ch = argv[1];
    cout<< "Get mode"<<ch[2]<<endl;
    return ch[2]-48;
}

void Interface::menu(int argc, char* argv[]) {
    if(argc == 1 ){
        cout << "Incorrect number of arguments ! At least 1 needed." << endl;
        printWaysToRunProgram();
    }
        cout << "argc: " << argc<<endl;
        int choice = getMode(argv);
        cout<< "choice" << choice<<endl;
            switch (choice) {
                case 1:
                    cout << "case 1" << endl;
                    logic->readGraphFromFile(argv[2]);
                    myGraph->printNeighbours();
                    logic->initializeNodesToConsiderVect(myGraph->getNumberOfNodes());
                    logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider(), logic->getRmsize());
                    break;
                case 2:
                    cout << "case 2" << endl;
                    GraphGenerator *graphGenerator;
                    graphGenerator = new GraphGenerator(5, 5, 2);
                    myGraph->setGraph(graphGenerator->generateGraph());
                    cout<<"**"<< myGraph->getNumberOfNodes()<<"**"<<endl;
                    myGraph->printNeighbours();
                    cout<<"****"<<endl;
                    logic->initializeNodesToConsiderVect(myGraph->getNumberOfNodes());
                    logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider(), logic->getRmsize());
                    break;
                case 3:
                    cout << "case 3" << endl;
                    // tu bedzie liczenie czasu który potem ma być zwrócony przez program
                    break;
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }

    }

