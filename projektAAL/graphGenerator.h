//
// Created by adell.j on 31.10.2018.
//

#ifndef PROJEKTAAL_GRAPHGENERATOR_H
#define PROJEKTAAL_GRAPHGENERATOR_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

class GraphGenerator {

private:
    int numberOfNodes;
    int numberOfEdges;
    int sizeOfBiggestClique;
    vector<int> generateNumbersWithoutRepetition(int number, int upperRange);
    void saveGraphToFile(string fileName, vector<vector<int>> graph);
    pair<int, int> generateVertice(vector<vector<int>> neighbours);
    bool verticeExists(pair<int, int>,  vector<vector<int>> neighbours);
    bool isElementInVector(vector<int> vector, int element);
    void setCliqueToGraph(vector<int> clique, vector<vector<int>> *neighbours);
    void setVerticeToGraph(pair<int, int> vertice, vector<vector<int>> *neighbours);
    void initializeAuxiliaryVector(vector<vector<int>> *neighbours);

public:
    GraphGenerator(int numOfNodes, int numOfEdges, int sizeOfBClique);
    ~GraphGenerator();
    pair<int, vector<vector<int>>> generateGraph();
};


#endif //PROJEKTAAL_GRAPHGENERATOR_H
