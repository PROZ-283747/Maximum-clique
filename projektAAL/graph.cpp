/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include <regex>
#include "graph.h"

Graph::Graph() : numberOfNodes(0) {
    cout<< "OMG znowu ten konstruktor." <<endl;
//    neighbours.push_back({1, 2});
//    neighbours.push_back({0, 2});
//    neighbours.push_back({0, 1, 3});
//    neighbours.push_back({2});

//    neighbours.push_back({1, 2, 3});
//    neighbours.push_back({0, 2, 3});
//    neighbours.push_back({0, 1, 3});
//    neighbours.push_back({0, 1, 2});
//    neighbours.push_back({3});

//    neighbours.push_back({2});
//    neighbours.push_back({2});
//    neighbours.push_back({0, 1});
//    neighbours.push_back({});

//    neighbours.push_back({2});
//    neighbours.push_back({2});
//    neighbours.push_back({0, 1});
//    neighbours.push_back({});

//    neighbours.push_back({3});
//    neighbours.push_back({2, 4, 5, 7});
//    neighbours.push_back({1, 4, 5,7});
//    neighbours.push_back({0, 4, 6, 7});
//    neighbours.push_back({1, 2, 5, 7, 6, 3});
//    neighbours.push_back({1, 2, 4, 7});
//    neighbours.push_back({3, 4, 7});
//    neighbours.push_back({6, 3, 4, 1, 2, 5});
//    neighbours.push_back({});
}

Graph::~Graph() {}

void Graph::setNumberOfNodes(int numOfNodes)
{
    numberOfNodes = numOfNodes;
}

void Graph::setNeighbours(vector<int> intVect){
    neighbours.push_back(intVect);
}

void Graph::printNeighbours(){
    cout<<"Print neighbours"<<endl;
    for(int i=0; i<neighbours.size(); ++i){
        for(int j=0; j<neighbours[i].size(); ++j){
            cout << neighbours[i][j]<< " ";
        }
        cout<<endl;
    }
}

const vector<vector<int>> &Graph::getNeighbours() const {
    return neighbours;
}

int Graph::getNumberOfNodes() const {
    return numberOfNodes;
}

void Graph::setGraph(pair<int , vector<vector<int>>> graphParams){
    numberOfNodes = graphParams.first;
    for(int i=0; i<numberOfNodes; ++i){
        cout<<"vhjmfhgfgb"<<endl;
        //neighbours[i].assign(graphParams.second[i].begin(), graphParams.second[i].end());
        neighbours.push_back(graphParams.second[i]);
        cout<<"vhjmfhgfgb"<<endl;
    }
}

