/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */
#ifndef PROJEKTAAL_LOGIC_H
#define PROJEKTAAL_LOGIC_H
#include <iostream>
#include <algorithm>
#include "graph.h"


using namespace std;

class Logic {
public:
    Logic(Graph *graph);
    ~Logic();
    int maximalCliqueSize; // biggest clique's size
    vector<int> maximalClique;
    void findBiggestClique(Graph *graph, vector<int> nodesToConsider, vector<int> partialResult);
    const vector<int> &getNodesToConsider() const;
    const vector<int> &getPartialResult() const;
    const vector<int> &getSkippedNodes() const;
    const int &getRmsize() const;
    void readGraphFromFile(string fileName);
    vector<int> changeStringVectorToInts(vector<string> strVect);
    void initializeNodesToConsiderVect(int numberOfNodes);
    void printResult();
    void setSkippedNodes(const vector<int> &skippedNodes);
    void setPartialResult(const vector<int> &partialResult);

private:
    Graph *myGraph;
    vector<int> nodesToConsider;
    vector<int> partialResult;
    vector<int> skippedNodes;
    bool isElementInVector(vector<int> vector, int element);
    int findPositionOfElementInVector(vector<int> vector, int element);
    void removeElementFromVector(vector<int>* vector,  int element);
    vector<int> productOfTwoVectors(vector<int> vect1, vector<int> vect2);
    void assignVectorToVector(vector<int>* vect1, vector<int> vect2);
    void printVector(vector<int>);
};


#endif //PROJEKTAAL_LOGIC_H
