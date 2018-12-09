/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */


#include "interface.h"

using namespace std;

// creates graph ad logic
Interface::Interface() {
    myGraph = new Graph();
    logic = new Logic2(myGraph);
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
        <<"3) program -m4 [numOfNodes] [sizeOfStep] [numOfSteps] (if you want to do statistics about complete graph)\n"
        <<"Specification for .txt files is in README\n\n"<<endl;
}
// Returns choosen mode
int Interface::getMode(char* argv[]){
    char *ch = argv[1];
    cout<< "Get mode"<<ch[2]<<endl;
    return ch[2]-48;
}

// m1: fileName, m2, m3: numOfNodes
int Interface::getSecondArg(char* argv[]){
    return stoi(argv[2]);
}

int Interface::getThirdArg(char* argv[]){
    return stoi(argv[3]);
}

int Interface::getFourthArg(char* argv[]){
    return stoi(argv[4]);
}

int Interface::getFifthArg(char* argv[]){
    return stoi(argv[5]);
}

int Interface::getSixthArg(char* argv[]){
    return stoi(argv[6]);
}

void Interface::menu(int argc, char* argv[]) {
    if(argc == 1 || argc == 2 ){
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
                    fileManager->readGraphFromFile(argv[2], myGraph);
                    myGraph->printNeighbours();
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    logic->printResult();
                    break;
                case 2:
                    cout << "case 2" << endl;
                    graphGenerator = new GraphGenerator(getSecondArg(argv), getThirdArg(argv), getFourthArg(argv));
                    myGraph->setGraph(graphGenerator->generateGraph());
                    myGraph->printNeighbours();
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    logic->printResult();
                    break;
                case 3: // Number of nodes is changed here
                    cout << "case 3" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i, 0, 5); // args: numberOfNodes, numberOfEdgesBesideClique, sizeOfClique,
                        myGraph->setGraph(graphGenerator->generateGraph());
                        //cout << "**" << myGraph->getNumberOfNodes() << "**" << endl;
                        //myGraph->printNeighbours();
                        //cout << "****" << endl;
                        logic->initializeLogic(myGraph->getNumberOfNodes());

                        int startTime = clock();

                        logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                        int endTime = clock();
                        logic->printResult();
                        cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
                        fileManager->saveResultToFile("../result4.txt", i, (float)(endTime-startTime)/CLOCKS_PER_SEC);
                    }
                    break;
                case 4: // Number of edges is changed here
                    cout << "case 4" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i);
                        myGraph->setGraph(graphGenerator->generateCompleteGraph());
                        logic->initializeLogic(myGraph->getNumberOfNodes());
                        int startTime = clock();
                        logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                        int endTime = clock();
                        logic->printResult();
                        cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC*1000 <<endl;
                        fileManager->saveResultToFile("../result4.txt", i, (float)(endTime-startTime)/CLOCKS_PER_SEC*1000);

                    }
                    break;
                case 5: // Analyse of complete graph with different number of nodes
                    cout << "case 4" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i);
                        myGraph->setGraph(graphGenerator->generateCompleteGraph());
                        int sumTime = 0;
                        int j = 0;
                        for(j = 0;  j< 20; ++j) {
                            int startTime = 0;
                            int endTime = 0;
                            logic->initializeLogic(myGraph->getNumberOfNodes());
                            startTime = clock();
                            logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                            endTime = clock();
                            sumTime += endTime - startTime;
                            //logic->printResult();
                            //cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC <<endl;
                        }
                        int averageTime = sumTime/j;
                        cout<<"Average time: "<< i <<" time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000 <<endl;
                        fileManager->saveResultToFile("../result8.txt", i, (float)(averageTime)/CLOCKS_PER_SEC*1000);
                    }
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }

    }

