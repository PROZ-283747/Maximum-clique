//
// Created by adell.j on 05.01.2019.
//

#ifndef PROJEKTAAL_HEURISTICALG_H
#define PROJEKTAAL_HEURISTICALG_H

#include <set>
#include <algorithm>
#include "graph.h"


class HeuristicAlg {
public:
    HeuristicAlg(Graph *graph);
    ~HeuristicAlg();
    void findMaximalClique();
    int getMaxDegree();
    void  printResult();
    void initializeNodesDegrees();

private:
    Graph *myGraph;
    set<int> maxClique;
    vector<int> nodesDegrees;
    int maxCliqueSize;
    void findClique(set<int> potentialNodes, int size, set<int> tempClique);
    int getNodeWithMaxDegree(set<int> nodes);
    set<int> getIntersection(set<int> A, set<int> B);
    void setNewMaxClique(set<int> clique);
};


#endif //PROJEKTAAL_HEURISTICALG_H
