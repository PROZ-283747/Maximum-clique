/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */


#include <complex>
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
// Returns chosen mode
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
                case 1: // reads graph from file, finds maximal clique and print it on console
                    //cout << "case 1" << endl;
                    fileManager->readGraphFromFile(argv[2], myGraph);
                    //myGraph->printNeighbours();
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    logic->printResult();
                    break;
                case 2: // generate single graph with number of nodes, max clique size and edges beside clique; than finds maximal clique
                    //cout << "case 2" << endl;
                    graphGenerator = new GraphGenerator(getSecondArg(argv), getThirdArg(argv), getFourthArg(argv));
                    myGraph->setGraph(graphGenerator->generateGraph());
                    //myGraph->printNeighbours();
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    logic->printResult();
                    break;
                case 3: // Number of nodes is constant and number of edges is incremented, edges  are random
                    cout << "case 3" << endl;
                    for(int i = stoi(argv[3]); i< stoi(argv[3])+(stoi(argv[4])*stoi(argv[5])); i+=stoi(argv[4])) {
                        graphGenerator = new GraphGenerator(stoi(argv[2]), i , 0); // args: numberOfNodes, numberOfEdgesBesideClique, sizeOfClique,
                        int sumTime = 0;
                        int j = 0;
                        for(j = 0;  j< 4; ++j) {
                            int startTime = 0;
                            int endTime = 0;
                            myGraph->setGraph(graphGenerator->generateGraph());
                            logic->initializeLogic(myGraph->getNumberOfNodes());
                            startTime = clock();
                            logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                            endTime = clock();
                            sumTime += endTime - startTime;
                            logic->printResult();
                            cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC*1000<<endl;
                        }
                        int averageTime = sumTime/j;
                        cout<<"Num od nodes: "<< i <<" Average time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000 <<endl;
                        fileManager->saveResultToFile("../30_5_5_85_toMax4.txt", i, (float)(averageTime)/CLOCKS_PER_SEC*1000);
                    }
                    break;
                case 4: // Number of edges is changed here, edges creates a constant path
                    cout << "case 4" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i, i-1);
                        myGraph->setGraph(graphGenerator->generatePathGraph());
                        logic->initializeLogic(myGraph->getNumberOfNodes());
                        myGraph->printNeighbours();
                        int startTime = clock();
                        logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                        int endTime = clock();
                        logic->printResult();
                        cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC*1000 <<endl;
                        fileManager->saveResultToFile("../result4.txt", i, (float)(endTime-startTime)/CLOCKS_PER_SEC*1000);
                    }
                    break;
                case 5: // Analyse of complete graph with different number of nodes
                    cout << "case 6" << endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {
                        graphGenerator = new GraphGenerator(i);
                        int sumTime = 0;
                        int j = 0;
                        for(j = 0; j< 4; ++j) {
                            int startTime = 0;
                            int endTime = 0;
                            myGraph->setGraph(graphGenerator->generateCompleteGraph());
                            logic->initializeLogic(myGraph->getNumberOfNodes());
                            startTime = clock();
                            logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                            endTime = clock();
                            sumTime += endTime - startTime;
                            logic->printResult();
                            //cout<<"i: "<< i <<" time: "<<(float)(endTime-startTime)/CLOCKS_PER_SEC <<endl;
                        }
                        int averageTime = sumTime/j;
                        cout<<"Num od nodes: "<< i <<" Average time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000<<endl;
                        fileManager->saveResultToFile("../fullGraphs.txt", i, (float)(averageTime)/CLOCKS_PER_SEC*1000);
                    }
                case 6: { // Analyse of complete graph with different number of nodes
                    cout << "case 6" << endl;
                    ofstream outputFile;
                    outputFile.open("../" + (string)argv[8], ios::app);
                    if (outputFile.is_open()) {
                        for (int i = stoi(argv[2]); i < stoi(argv[2]) + (stoi(argv[3]) * stoi(argv[4])); i += stoi(argv[3])) {
                            outputFile << i << " ";
                            for (int j = stoi(argv[5]);j < stoi(argv[5]) + (stoi(argv[6]) * stoi(argv[7])); j += stoi(argv[6])) {
                                int sumTime = 0;
                                if(i*(i-1)/2 < j) {
                                    outputFile << "-" << " ";
                                    break;
                                }
                                else{
                                    graphGenerator = new GraphGenerator(i, j, 0);
                                    cout<<"i: " << i<<endl;
                                    cout<<"j: " << j<<endl;
                                    for (int k = 0; k < 4; ++k) {
                                        int startTime = 0;
                                        int endTime = 0;
                                        myGraph->setGraph(graphGenerator->generateGraph());
                                        logic->initializeLogic(myGraph->getNumberOfNodes());
                                        startTime = clock();
                                        logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                                        endTime = clock();
                                        sumTime += endTime - startTime;
                                        logic->printResult();
                                    }
                                }
                                int averageTime = sumTime / j;
                                cout << "Num od nodes: " << i << " Average time: " << (float) (averageTime) / CLOCKS_PER_SEC * 1000 << endl;
                                outputFile << (float) (averageTime) / CLOCKS_PER_SEC * 1000 << " ";
                            }
                            outputFile << '\n';
                        }
                    } else
                        cout << "Saving to file failed.";
                    outputFile.close();
                }
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }

    }

