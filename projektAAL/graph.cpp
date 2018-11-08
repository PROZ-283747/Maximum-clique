//
// Created by adell.j on 01.11.2018.
//

#include "graph.h"

Graph::Graph() : numberOfNodes(5) {
//    neighbours.push_back({1, 2});
//    neighbours.push_back({0, 2});
//    neighbours.push_back({0, 1, 3});
//    neighbours.push_back({2});
    neighbours.push_back({1, 2, 3});
    neighbours.push_back({0, 2, 3});
    neighbours.push_back({0, 1, 3});
    neighbours.push_back({0, 1, 2});
    neighbours.push_back({3});
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

//void Graph::setNeighbours() {
//}

void Graph::printNeighbours(){
    for(int i=0; i<neighbours.size(); ++i){
        for(int j=0; j<neighbours[i].size(); ++j){
            cout << neighbours[i][j]<< " ";
        }
        cout<<endl;
    }
}

void Graph::printNumberOfNodes() {
    cout<<"Number of nodes: "<< numberOfNodes <<endl;
}

const vector<vector<int>> &Graph::getNeighbours() const {
    return neighbours;
}



