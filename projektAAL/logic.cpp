/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */
#include <regex>
#include "logic.h"


Logic::Logic(Graph *graph) : maximalCliqueSize(0) {
    cout<<"To ma sie wywolywac" << endl;
    myGraph = graph;
    partialResult.clear();
    skippedNodes.clear();
    nodesToConsider.clear();
}

Logic::~Logic() {}

void Logic::initializeNodesToConsiderVect(int numberOfNodes){
    for(int i=0; i< numberOfNodes; ++i){
        nodesToConsider.push_back(i);
    }
    maximalClique.clear();
    maximalCliqueSize =0;
    numOfRecursion = 0;
}

void Logic::assignVectorToVector(vector<int>* vect1, vector<int> vect2){
    vect1->assign(vect2.begin(), vect2.end());
}

vector<int> Logic::productOfTwoVectors(vector<int> vect1, vector<int> vect2){
    vector<int> vector;
    for(int i=0; i<vect1.size(); ++i){
        if(isElementInVector(vect2, vect1[i]))
            vector.push_back(vect1[i]);
    }
    return vector;
}

bool Logic::isElementInVector(vector<int> vector, int element){
    find(vector.begin(), vector.end(), element) != vector.end();
}

int Logic::findPositionOfElementInVector(vector<int> vector, int element){
    for(int i=0; i< vector.size(); ++i){
        if(vector[i] ==  element)
            return i;
    }
    return -1;
}

void Logic::removeElementFromVector(vector<int>* vector, int element){
    if(isElementInVector(*vector, element)) {
        vector->erase(vector->begin() + findPositionOfElementInVector(*vector, element));
    }
    return;
}

void Logic::printVector(vector<int> vector){
    for(int i=0; i< vector.size(); ++i){
        cout<< vector[i] << " ";
    }
    cout<<endl;
}

// wywołaj później to w algorytmie
int Logic::findPiwot(vector<int>* vector){
    int v; //piwot to return
    int ncmax = 0;
    // dla każdego wierzchołka w P"
    for(int i = 0; i < nodesToConsider.size(); ++i) {
        int nc = 0;
        int u = nodesToConsider[i]; // wierzchołek z P" - indeks w neighbours
        // dla każdego sąsiada wierzchołka u z P"
        for (int j = 0; j < myGraph->getNeighbours()[u].size(); ++j) {
            for (int k = 0; k < nodesToConsider.size(); ++k) {
                if (myGraph->getNeighbours()[u][j] == nodesToConsider[k])
                    nc++;
            }
        }
        if (nc >= ncmax) {
            v = u;   // piwot
            ncmax = nc;
        }
    }
    return v;
}

void Logic::findBiggestClique(Graph *graph, vector<int> partialResult, vector<int> nodesToConsider) {
    //cout << endl;
    //cout << "Find biggest clique" << endl;
    //cout << "P: "; printVector(nodesToConsider);
    //cout << "R: "; printVector(partialResult);
    numOfRecursion++;
    vector<int> nodesToConsiderPrimP;
    vector<int> nodesToConsiderBisP;
    vector<int> partialResultPrimR;
    vector<int> tempNodesN;
    int u = 0, v = 0, ncmax = 0, nc = 0, rms = 0;

    if (nodesToConsider.empty()) {
        rms = partialResult.size();
        if (rms >= maximalCliqueSize) {
            maximalClique.assign(partialResult.begin(), partialResult.end());
            maximalCliqueSize = rms;
        }
    } else {
        ncmax = 0;
        // dla każdego wierzchołka w P"
        for (int i = 0; i < nodesToConsider.size(); ++i) {
            nc = 0;
            u = nodesToConsider[i]; // wierzchołek z P" - indeks w neighbours
            // dla każdego sąsiada wierzchołka u z P"
            for (int j = 0; j < myGraph->getNeighbours()[u].size(); ++j) {
                for (int k = 0; k < nodesToConsider.size(); ++k) {
                    if (myGraph->getNeighbours()[u][j] == nodesToConsider[k])
                        nc++;
                }
            }
            if (nc >= ncmax) {
                v = u;   // piwot
                ncmax = nc;
            }
            // TODO: Później else na górze zastąpić tą jedną linijką
            //v = findPiwot(&nodesToConsider); // finds node with the biggest number of neighbours in nodesToConsider vector
        }
        nodesToConsiderBisP.assign(nodesToConsider.begin(), nodesToConsider.end());
        for (int i = 0; i < myGraph->getNeighbours()[v].size(); ++i) {
            removeElementFromVector(&nodesToConsiderBisP, myGraph->getNeighbours()[v][i]);
        }
        nodesToConsiderPrimP.clear();
        partialResultPrimR.clear();
        for (int i = 0; i < nodesToConsiderBisP.size(); ++i) {
            u = nodesToConsiderBisP[i];
            tempNodesN.clear();
            for (int j = 0; j < myGraph->getNeighbours()[u].size(); ++j) {
                tempNodesN.push_back(myGraph->getNeighbours()[u][j]);
            }
            partialResultPrimR.assign(partialResult.begin(), partialResult.end());
            partialResultPrimR.push_back(u); // było v a nie u
            assignVectorToVector(&nodesToConsiderPrimP, productOfTwoVectors(nodesToConsider, tempNodesN));

            findBiggestClique(graph, partialResultPrimR, nodesToConsiderPrimP);

            removeElementFromVector(&nodesToConsider, v);  // P - v
        }
    }
}



void Logic::printResult() {
    cout<<"MAXIMAL CLIQUE: "; printVector(maximalClique);
    cout<< "SIZE: "<< maximalCliqueSize<<endl;
    cout<< "NUMofRECURSION: "<< numOfRecursion<<endl;
}
const vector<int> &Logic::getNodesToConsider() const {
    return nodesToConsider;
}

const vector<int> &Logic::getPartialResult() const {
    return partialResult;
}

const vector<int> &Logic::getSkippedNodes() const {
    return skippedNodes;
}

const int &Logic::getRmsize() const {
    return maximalCliqueSize;
}

void Logic::setPartialResult(const vector<int> &partialResult) {
    Logic::partialResult = partialResult;
}

void Logic::setSkippedNodes(const vector<int> &skippedNodes) {
    Logic::skippedNodes = skippedNodes;
}



