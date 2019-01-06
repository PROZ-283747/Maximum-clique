//
// Created by adell.j on 05.01.2019.
//

#include "heuristicAlg.h"


HeuristicAlg::HeuristicAlg(Graph *graph){
    cout<<"Konstruktor" << endl;
    myGraph = graph;
    maxCliqueSize = 0;
    maxClique.clear();
}

HeuristicAlg::~HeuristicAlg() {}

//initializes vector with degrees with nodes for faster access
void HeuristicAlg::initializeNodesDegrees() {
    nodesDegrees.clear();
    for(int i = 0; i < myGraph->getNeighbours().size(); ++i){
        nodesDegrees.push_back(myGraph->getNeighbours()[i].size());
    }
}

void HeuristicAlg::printResult() {
    std::cout<<"H:MAX SIZE: "<< maxCliqueSize<<std::endl;
    std::cout<<"H:MAX CLIQUE: ";
    for(auto it = maxClique.begin(); it != maxClique.end(); ++it){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
}

int HeuristicAlg::getMaxDegree() {
    int maxDegree = 0;
    for(int i = 0; i < nodesDegrees.size(); ++i)
        if(maxDegree < nodesDegrees[i])
            maxDegree = nodesDegrees[i];

     return maxDegree;
}

int HeuristicAlg::getNodeWithMaxDegree(set<int> nodes){
    int maxDegree = 0;
    int maxDegreeNode = 0;
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
        if(nodesDegrees[*it] > maxDegree){
            maxDegree = nodesDegrees[*it];
            maxDegreeNode = *it;
        }
    }
    return maxDegreeNode;
}

set<int> HeuristicAlg::getIntersection(set<int> A, set<int> B) {
    //cout<< "getIntersection"<<endl;
    set<int> intersectionSet;
    auto itA = A.begin();
    auto itB = B.begin();
    while (itA != A.end() && itB != B.end()) {
        if (*itA == *itB) {
            intersectionSet.insert(*itA);
            ++itA;
            ++itB;
        } else {
            if (*itA > *itB) {
                ++itB;
            }
            if (*itA < *itB) {
                ++itA;
            }
        }
    }
    return intersectionSet;
}

void HeuristicAlg::setNewMaxClique(set<int> clique){
    //cout<< "setNewMaxClique"<<endl;
    maxClique.clear();
    maxClique.insert(clique.begin(), clique.end());
    maxCliqueSize = clique.size();
}

void HeuristicAlg::findMaximalClique() {
    set<int> U;
    set<int> tempClique;
    for(int i = 0; i < myGraph->getNeighbours().size(); ++i){
        tempClique.clear();
        if(nodesDegrees[i] >= maxCliqueSize) {
            U.clear();
            tempClique.insert(i); // ***
            for(int j = 0; j < myGraph->getNeighbours()[i].size(); ++j){
                if(nodesDegrees[myGraph->getNeighbours()[i][j]] >= maxCliqueSize)
                    U.insert(myGraph->getNeighbours()[i][j]);
            }
            findClique(U, 1, tempClique);
        }
    }
}

void HeuristicAlg::findClique(set<int> potentialNodes, int size, set<int> tempClique) {
    if(potentialNodes.empty()) {
        if (size > maxCliqueSize) {
            maxCliqueSize = size;
            setNewMaxClique(tempClique);
        }
        return;
    }
    int node = getNodeWithMaxDegree(potentialNodes);
    potentialNodes.erase(node);
    tempClique.insert(node); // ***
    set<int> N;
    N.clear();
    // adds to N' all neighbours of 'node' possible to add to the clique
    for(int i =0; i < myGraph->getNeighbours()[node].size(); ++i){
        if(nodesDegrees[myGraph->getNeighbours()[node][i]] >= maxCliqueSize)
            N.insert(myGraph->getNeighbours()[node][i]);
    }

    findClique(getIntersection(potentialNodes, N), size+1, tempClique);
}


