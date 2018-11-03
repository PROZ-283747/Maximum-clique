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
    vector<vector<int>> adjacencyMatrix;
public:
    void setAdjacencyMatrix(const vector<vector<int>> &adjacencyMatrix);

public:
    const vector<vector<int>> &getAdjacencyMatrix() const;

public:
    Graph();
    ~Graph();
    int getNumberOfNodes();
    void setNumberOfNodes(int numberOfNodes);
    void printNumberOfNodes();
    void setZerosToMarix();
    void setAdjecencyMatrix(int first, int second);
    void printAdjecencyMatrix();

};


#endif //PROJEKTAAL_GRAPH_H
