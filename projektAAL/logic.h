//
// Created by adell.j on 01.11.2018.
//

#ifndef PROJEKTAAL_LOGIC_H
#define PROJEKTAAL_LOGIC_H
#include <iostream>
#include <algorithm>
#include "graph.h"

using namespace std;

class Logic {
public:
    Logic();
    Logic(Graph *graph);
    ~Logic();
    int rmsize; // biggest clique's size
    vector<int> findBiggestClique(Graph *graph, vector<int> nodesToConsider, vector<int> partialResult, vector<int> skippedNodes, int rmsize);
    const vector<int> &getNodesToConsider() const;
    const vector<int> &getPartialResult() const;
    const vector<int> &getSkippedNodes() const;
    const int &getRmsize() const;
    void setNodesToConsider(const vector<int> &nodesToConsider);
    void setSkippedNodes(const vector<int> &skippedNodes);
    void setPartialResult(const vector<int> &partialResult);
    void addNodesToCandidatesList();

private:
    Graph *myGraph;
    vector<int> nodesToConsider;
    vector<int> partialResult;
    vector<int> skippedNodes;
    void initializeNodesToConsiderVect();
    //void addNodesToCandidatesList(Graph *graph, vector<int> vector);
    bool isElementInVector(vector<int> vector, int element);
    int findPositionOfElementInVector(vector<int> vector, int element);
    void removeElementFromVector(vector<int>* vector,  int element);
    vector<int> productOfTwoVectors(vector<int> vect1, vector<int> vect2);
    void assignVectorToVector(vector<int>* vect1, vector<int> vect2);
    void printVector(vector<int>);
};


#endif //PROJEKTAAL_LOGIC_H
