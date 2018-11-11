/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

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
    void readGraphFromFile(string fileName);
    vector<int> changeStringVectorToInts(vector<string> strVect);

public:
    Graph(string fileName);
    Graph(char* argv[]);
    ~Graph();
    const vector<vector<int>> &getNeighbours() const;
    int getNumberOfNodes() const;
    void setNumberOfNodes(int numberOfNodes);
    void setNeighbours(vector<int> intVect);
    void printNeighbours();
};


#endif //PROJEKTAAL_GRAPH_H
