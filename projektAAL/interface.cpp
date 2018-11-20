/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */


#include "interface.h"

using namespace std;

// creates graph
Interface::Interface() {
    myGraph = new Graph();
    logic = new Logic(myGraph);
}

Interface::~Interface() {
    delete myGraph;
    delete logic;
}

// Prints possible ways to run program
void Interface::printWaysToRunProgram() {
    cout<<"\nThis program can be used to find the biggest clique in a graph\n";
    cout<<"To run it you need to enter: \n"
        <<"1) program -m1 graph.txt (if you want to read graph from file)\n"
        <<"2) program -m2 [numOfNodes] [numOfEdges] [sizeOfMaxClique] (if you want to generate graph)\n"
        <<"3) program -m3 [numOfNodes] [sizeOfStep] [numOfSteps] (if you want to do statistics)\n"
        <<"Specification for .txt files is in README\n\n"<<endl;
}
// Returns choosen program mode
int Interface::getMode(char* argv[]){
    char *ch = argv[1];
    cout<< "Get mode"<<ch[2]<<endl;
    return ch[2]-48;
}

int Interface::getSecondArg(char* argv[]){
    return stoi(argv[2]);
}

int Interface::getThirdArg(char* argv[]){
    return stoi(argv[3]);
}

int Interface::getFourthArg(char* argv[]){
    return stoi(argv[4]);
}

void Interface::menu(int argc, char* argv[]) {
    if(argc == 1 ){
        cout << "Incorrect number of arguments ! At least 1 needed." << endl;
        printWaysToRunProgram();
    }
        srand( time( NULL ) );
        cout << "argc: " << argc<<endl;
        int choice = getMode(argv);
        cout<< "choice" << choice<<endl;
        GraphGenerator *graphGenerator;
        srand( time( NULL ) );
            switch (choice) {
                case 1:
                    cout << "case 1" << endl;
                    logic->readGraphFromFile(argv[2]);
                    myGraph->printNeighbours();
                    logic->initializeNodesToConsiderVect(myGraph->getNumberOfNodes());
                    logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider());
                    break;
                case 2:
                    cout << "case 2" << endl;
                    cout << "Edges: " << stoi(argv[3])<<endl;
                    graphGenerator = new GraphGenerator(getSecondArg(argv), getThirdArg(argv), getFourthArg(argv));
                    myGraph->setGraph(graphGenerator->generateGraph());
                    cout<<"**"<< myGraph->getNumberOfNodes()<<"**"<<endl;
                    myGraph->printNeighbours();
                    cout<<"****"<<endl;
                    logic->initializeNodesToConsiderVect(myGraph->getNumberOfNodes());
                    logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider());
                    break;
                case 3:
                    cout << "case 3" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i, 40, 5);
                        myGraph->setGraph(graphGenerator->generateGraph());
                        //cout << "**" << myGraph->getNumberOfNodes() << "**" << endl;
                        //myGraph->printNeighbours();
                        //cout << "****" << endl;
                        logic->initializeNodesToConsiderVect(myGraph->getNumberOfNodes());

                        int startTime = clock();
                        logic->findBiggestClique(myGraph, logic->getPartialResult(), logic->getNodesToConsider());
                        int endTime = clock();
                        logic->printResult();
                        cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC <<endl;
                        fileManager->saveResultToFile("../result.txt", i, (float)(endTime-startTime)/CLOCKS_PER_SEC );
                    }
                    break;
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }

    }

