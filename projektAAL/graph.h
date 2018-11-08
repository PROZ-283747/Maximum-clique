//
// Created by adell.j on 01.11.2018.
//

#ifndef PROJEKTAAL_GRAPH_H
#define PROJEKTAAL_GRAPH_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Graph {
private:
    int numberOfNodes;
    vector<vector<int>> neighbours;
public:
    Graph();
    ~Graph();
    const vector<vector<int>> &getNeighbours() const;
    int getNumberOfNodes();
    void setNumberOfNodes(int numberOfNodes);
    void printNumberOfNodes();
//    void setNeighbours();
    void printNeighbours();
};


#endif //PROJEKTAAL_GRAPH_H
