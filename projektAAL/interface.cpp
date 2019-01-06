/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */


#include <complex>
#include "interface.h"

using namespace std;

// creates graph ad logic
Interface::Interface() {
    myGraph = new Graph();
    logic = new Logic2(myGraph);
    heurAlg = new HeuristicAlg(myGraph);
}

Interface::~Interface() {
    delete myGraph;
    delete logic;
    delete heurAlg;
}

// Prints possible ways to run program
void Interface::printWaysToRunProgram() {
    cout<<"\nThis program can be used to find maximal clique in a graph\n";
    cout<<"Ways to run it: \n"
        <<"1) program -m1 graph.txt (if you want to read graph from file)\n"
        <<"2) program -m2 [numOfNodes] [numOfEdges] [sizeOfMaxClique] (if you want to generate one graph)\n"
        <<"3) program -m3 [numOfNodes] [initNumOfEdges][sizeOfStep] [numOfSteps] (if you want to do statistics for graphs with n nodes and incremented number od edges)\n"
        <<"3) program -m4 [initNumOfNodes] [sizeOfStep] [numOfSteps] (if you want to do statistics about complete graphs)\n"
        <<"3) program -m5 [initNumOfNodes] [sizeOfStep] [numOfSteps] (if you want to do statistics about almost complete graph (worst case))\n"
        <<"More information in README.txt\n\n"<<endl;
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
    if(argc == 1 ){
        cout << "Incorrect number of arguments ! At least 1 needed." << endl;
        printWaysToRunProgram();
    }
        int choice = getMode(argv);
        cout<< "choice" << choice<<endl;
        GraphGenerator *graphGenerator;
        srand( time( NULL ) );
            switch (choice) {
                case 1: // reads graph from file, finds maximal clique:  na razie: -m1 pilk.txt | później: -m1 << plik.txt

                    // TODO: zamienić na strumień
                    fileManager->readGraphFromFile(argv[2], myGraph);
                    myGraph->printNeighbours();

                    // prepare data for algorithms to find clique
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    heurAlg->initializeNodesDegrees();

                    // finds maximal cliques
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    heurAlg->findMaximalClique();

                    // prints results
                    logic->printResult();
                    heurAlg->printResult();

                    break;
                case 2: // generate single graph with number of nodes, max clique size and edges beside clique; than finds maximal clique

                    // generates graph and print it
                    graphGenerator = new GraphGenerator(getSecondArg(argv), getThirdArg(argv), getFourthArg(argv));
                    myGraph->setGraph(graphGenerator->generateGraph());
                    myGraph->printNeighbours();

                    // prepare data for algorithms to find clique
                    logic->initializeLogic(myGraph->getNumberOfNodes());
                    heurAlg->initializeNodesDegrees();

                    // finds maximal cliques
                    logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                    heurAlg->findMaximalClique();

                    // prints results
                    logic->printResult();
                    heurAlg->printResult();

                    break;
                case 3: // Constatnt number of nodes, number of edges incremented in every step: -m3 [n] [m] [step] [numOfSteps]
                    cout << "n bronKerboschAlgTime heuristicAlgTime "<< endl;
                    for(int i = stoi(argv[3]); i< stoi(argv[3])+(stoi(argv[4])*stoi(argv[5])); i+=stoi(argv[4])) {
                        graphGenerator = new GraphGenerator(stoi(argv[2]), i , 0); // args: numberOfNodes, numberOfEdgesBesideClique, sizeOfClique,
                        int sumTime = 0, sumTimeH = 0;
                        int j = 0;
                        for(j = 0;  j< 4; ++j) {
                            int startTime = 0, endTime = 0, startTimeH = 0, endTimeH = 0;

                            // prepare data for algorithms to find clique
                            myGraph->setGraph(graphGenerator->generateGraph());
                            logic->initializeLogic(myGraph->getNumberOfNodes());
                            heurAlg->initializeNodesDegrees();

                            // count time for Bron-Kerbosch algorithm
                            startTime = clock();
                            logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                            endTime = clock();

                            // counts time for heuristic algorithm
                            startTimeH = clock();
                            heurAlg->findMaximalClique();
                            endTimeH = clock();

                            sumTime += endTime - startTime;
                            sumTimeH += endTimeH - startTimeH;

                            //print results
                            //logic->printResult();
                            //heurAlg->printResult();
                        }
                        int averageTime = sumTime/j;
                        int averageTimeH = sumTimeH/j;
                        //cout<<"n: "<< i <<" A:Average time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000 <<endl;
                        //cout<<"n: "<< i <<" H:Average time: "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                        cout<<i<<" "<<(float)(averageTime)/CLOCKS_PER_SEC*1000<<" "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                    }
                    break;

                case 4: // Analyse of complete graph with different number of nodes
                        cout << "n bronKerboschAlgTime heuristicAlgTime "<< endl;
                        for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {

                            graphGenerator = new GraphGenerator(i, i*(i-1)/2 , 0); // args: numberOfNodes, numberOfEdgesBesideClique, sizeOfClique,
                            int sumTime = 0, sumTimeH = 0;
                            int j = 0;
                            for(j = 0;  j< 4; ++j) {
                                int startTime = 0, endTime = 0, startTimeH = 0, endTimeH = 0;

                                // prepare data for algorithms to find clique
                                myGraph->setGraph(graphGenerator->generateGraph());
                                logic->initializeLogic(myGraph->getNumberOfNodes());
                                heurAlg->initializeNodesDegrees();

                                // count time for Bron-Kerbosch algorithm
                                startTime = clock();
                                logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                                endTime = clock();

                                // counts time for heuristic algorithm
                                startTimeH = clock();
                                heurAlg->findMaximalClique();
                                endTimeH = clock();

                                sumTime += endTime - startTime;
                                sumTimeH += endTimeH - startTimeH;

                                //print results
                                //logic->printResult();
                                //heurAlg->printResult();
                            }
                            int averageTime = sumTime/j;
                            int averageTimeH = sumTimeH/j;
                            //cout<<"n: "<< i <<" A:Average time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000 <<endl;
                            //cout<<"n: "<< i <<" H:Average time: "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                            cout<<i<<" "<<(float)(averageTime)/CLOCKS_PER_SEC*1000<<" "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                        }
                        break;
                // worst case: -m5 [n] [step] [numOfSteps]
                case 5: {
                    cout << "n bronKerboschAlgTime heuristicAlgTime "<< endl;
                    for(int i = stoi(argv[2]); i< stoi(argv[2])+(stoi(argv[3])*stoi(argv[4])); i+=stoi(argv[3])) {

                        graphGenerator = new GraphGenerator(i, i*(i-1)/2-i , 0); // args: numberOfNodes, numberOfEdgesBesideClique, sizeOfClique,
                        int sumTime = 0, sumTimeH = 0;
                        int j = 0;
                        for(j = 0;  j< 4; ++j) {
                            int startTime = 0, endTime = 0, startTimeH = 0, endTimeH = 0;

                            // prepare data for algorithms to find clique
                            myGraph->setGraph(graphGenerator->generateGraph());
                            logic->initializeLogic(myGraph->getNumberOfNodes());
                            heurAlg->initializeNodesDegrees();

                            // count time for Bron-Kerbosch algorithm
                            startTime = clock();
                            logic->findMaximalClique(logic->getR(), logic->getP(), logic->getX());
                            endTime = clock();

                            // counts time for heuristic algorithm
                            startTimeH = clock();
                            heurAlg->findMaximalClique();
                            endTimeH = clock();

                            sumTime += endTime - startTime;
                            sumTimeH += endTimeH - startTimeH;

                            //print results
                            //logic->printResult();
                            //heurAlg->printResult();
                        }
                        int averageTime = sumTime/j;
                        int averageTimeH = sumTimeH/j;
                        //cout<<"n: "<< i <<" A:Average time: "<<(float)(averageTime)/CLOCKS_PER_SEC*1000 <<endl;
                        //cout<<"n: "<< i <<" H:Average time: "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                        cout<<i<<" "<<(float)(averageTime)/CLOCKS_PER_SEC*1000<<" "<<(float)(averageTimeH)/CLOCKS_PER_SEC*1000 <<endl;
                    }
                    break;
                }
                default:
                    cout<< "default: ";
                    printWaysToRunProgram();
                    break;
            }

    }

