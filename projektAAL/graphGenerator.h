/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */


#ifndef PROJEKTAAL_GRAPHGENERATOR_H
#define PROJEKTAAL_GRAPHGENERATOR_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include "fileManager.h"

using namespace std;

class GraphGenerator {

private:
    int numberOfNodes;
    int numberOfEdges;
    int sizeOfBiggestClique;
    vector<int> generateNumbersWithoutRepetition(int number, int upperRange);
    pair<int, int> generateEdge(vector<vector<int>> neighbours);
    bool edgeExists(pair<int, int>,  vector<vector<int>> neighbours);
    bool isElementInVector(vector<int> vector, int element);
    void setCliqueToGraph(vector<int> clique, vector<vector<int>> *neighbours);
    void setEdgeToGraph(pair<int, int> vertice, vector<vector<int>> *neighbours);
    void initializeAuxiliaryVector(vector<vector<int>> *neighbours);

public:
    GraphGenerator(int numOfNodes, int numOfEdges, int sizeOfBClique);
    ~GraphGenerator();
    pair<int, vector<vector<int>>> generateGraph();
};


#endif //PROJEKTAAL_GRAPHGENERATOR_H
