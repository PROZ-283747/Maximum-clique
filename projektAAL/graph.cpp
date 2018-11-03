//
// Created by adell.j on 01.11.2018.
//

#include "graph.h"

Graph::Graph() : numberOfNodes(0) {
    cout << "Constructor. Size: "<< adjacencyMatrix.size() <<endl;
}

Graph::~Graph() {}

int Graph::getNumberOfNodes()
{
    return numberOfNodes;
}

void Graph::setNumberOfNodes(int numOfNodes)
{
    numberOfNodes = numOfNodes;
}

void Graph::setZerosToMarix() {
    vector<int> tempVector;
    for(int j=0; j<numberOfNodes; ++j){
        tempVector.push_back(0);
    }
    for(int i=0; i<numberOfNodes; ++i){
        adjacencyMatrix.push_back(tempVector);
    }
}

void Graph::setAdjecencyMatrix(int first, int second) {
    adjacencyMatrix[first][second] = 1;
}

void Graph::printAdjecencyMatrix(){
    for(int i=0; i<numberOfNodes; ++i){
        for(int j=0; j<numberOfNodes; ++j){
            cout << adjacencyMatrix[i][j]<< " ";
        }
        cout<<endl;
    }
}

void Graph::printNumberOfNodes() {
    cout<<"Number of nodes: "<< numberOfNodes <<endl;
}

const vector<vector<int>> &Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

void Graph::setAdjacencyMatrix(const vector<vector<int>> &adjacencyMatrix) {
    Graph::adjacencyMatrix = adjacencyMatrix;
}
