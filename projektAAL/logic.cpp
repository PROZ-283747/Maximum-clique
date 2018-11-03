//
// Created by adell.j on 01.11.2018.
//

#include "logic.h"

Logic::Logic(){
   cout<< "To bez parametrów. Ma sie nie wywoływac "<<endl;
}

Logic::Logic(Graph *graph) {
    cout<<"To ma sie wywolywac" << endl;
    myGraph = graph;
}

Logic::~Logic() {}

void Logic::assignVectorToVector(vector<int> vect1, vector<int> vect2){
    vect1.assign(vect2.begin(), vect2.end());
}

vector<int> Logic::productOfTwoVectors(vector<int> vect1, vector<int> vect2){
    vector<int> vector;
    for(int i=0; i<vect1.size(); ++i){
        for(int j=0; j<vect2.size(); ++j){
            if(vect1[i]==vect2[j])
                vector.push_back(vect1[i]);
        }
    }
    return vect1;
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

void Logic::removeElementFromVector(vector<int> vector, int element){
    if(isElementInVector(vector, element)) {
        vector.erase(vector.begin() + findPositionOfElementInVector(vector, element));
    }
    return;
}

void Logic::printVector(vector<int> vector){
    for(int i=0; i< vector.size(); ++i){
        cout<< vector[i] << " ";
    }
    cout<<endl;
}

vector<int> Logic::findBiggestClique(Graph *graph, vector<int> partialResult, vector<int> nodesToConsider, vector<int> skippedNodes){
    cout<<"Find biggest clique"<<endl;
    cout<<"Nodes to consider: "; printVector(nodesToConsider);

    vector<int> nodesToConsiderPrimP;
    vector<int> nodesToConsiderBisP;
    vector<int> partialResultPrimR;
    vector<int> skippedNodesPrimX;
    vector<int> tempNodesN;
    vector<int> biggestCliqueRM;
    int u=0, v=0, w=0, ncmax=0, nc=0, rms=0;
    int bCliqueSize=0; // biggest clique's size

    if(nodesToConsider.empty() && skippedNodes.empty()){
        rms = partialResult.size();
        if(rms > bCliqueSize){
            biggestCliqueRM.clear();
            biggestCliqueRM.assign(partialResult.begin(), partialResult.end());
            bCliqueSize = rms;
        }
        cout<<"BIGGEST: ";
        printVector(biggestCliqueRM);
        return biggestCliqueRM;
    }
    else {
        cout<<"ELSE"<<endl;
        nodesToConsiderBisP.clear();
        for (int i = 0; i < nodesToConsider.size(); ++i) {

            nodesToConsiderBisP.push_back(nodesToConsider[i]);
        }
        for (int i = 0; i < skippedNodes.size(); ++i) {
            nodesToConsiderBisP.push_back(skippedNodes[i]);
        }
        ncmax = 0;
        for(u=0; u< nodesToConsiderBisP.size(); ++u){
            nc = 0;
            vector<int> neighbours;
            for(int i=0; i< graph->getAdjacencyMatrix().size(); ++i) {
                neighbours.push_back(graph->getAdjacencyMatrix()[u][i]);
            }
            for(w=0; w< neighbours.size(); ++w){
                for(int i=0; i< nodesToConsider.size(); ++i){
                    if (neighbours[w] == nodesToConsider[i])
                        nc++;
                }
            }
            if(nc >= ncmax){
                v = u;
                ncmax = nc;
            }
            nodesToConsiderBisP.clear();
            nodesToConsiderBisP.assign(nodesToConsider.begin(), nodesToConsider.end());
            for(int i=0; i<neighbours.size(); ++i) {
                removeElementFromVector(nodesToConsiderBisP, neighbours[i]);
            }
            tempNodesN.clear();
            for(int i=0; i<neighbours.size(); ++i) {
                tempNodesN.push_back(neighbours[i]);
            }
            partialResultPrimR.push_back(v);
            assignVectorToVector(nodesToConsiderPrimP, productOfTwoVectors(nodesToConsider, tempNodesN));
            assignVectorToVector(skippedNodesPrimX, productOfTwoVectors(skippedNodes, tempNodesN));

            findBiggestClique(graph, partialResultPrimR, nodesToConsiderPrimP, skippedNodesPrimX);

            removeElementFromVector(nodesToConsider,  v);
            partialResult.push_back(v);
        }
    }
}


void Logic::addNodesToCandidatesList(){
    cout<< "addNodesToCandidatesList"<<endl;
    cout<< myGraph->getNumberOfNodes()<<endl;
    for(int i=0; i< myGraph->getNumberOfNodes(); ++i){
        cout<< "i: "<< i <<endl;
        nodesToConsider.push_back(i);
    }
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

void Logic::setPartialResult(const vector<int> &partialResult) {
    Logic::partialResult = partialResult;
}

void Logic::setSkippedNodes(const vector<int> &skippedNodes) {
    Logic::skippedNodes = skippedNodes;
}

void Logic::setNodesToConsider(const vector<int> &nodesToConsider) {
    Logic::nodesToConsider = nodesToConsider;
}

