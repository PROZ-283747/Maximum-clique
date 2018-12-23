//
// Created by adell.j on 07.12.2018.
//

#ifndef PROJEKTAAL_LOGIC2_H
#define PROJEKTAAL_LOGIC2_H

#include <set>
#include "graph.h"

using namespace std;

class Logic2 {
public:
    Logic2(Graph *graph);
    ~Logic2();
    void initializeLogic(int numOfNodes);
    void findMaximalClique(set<int> R, set<int> P, set<int> X);
    void printResult();
    void setP(const set<int> &P);
    void setR(const set<int> &R);
    void setX(const set<int> &X);
    const set<int> &getP() const;
    const set<int> &getR() const;
    const set<int> &getX() const;

private:
    Graph *myGraph;
    set<int> maxClique;
    int maxCliqueSize;
    set<int> P;
    set<int> R;
    set<int> X;
    int numOfRecursion;
    int numOfSimpleInstruction;
    void fillInNodesToP(int numOfNodes);
    bool isMaxBigger(set<int> R);
    void setNewMaxClique(set<int> R);
    set<int> getUnion(set<int> A, set<int> B);
    set<int> getIntersection(set<int> A, set<int> B);
    int findPivot(set<int> set);
    set<int> substractSet(set<int> setFrom, vector<int> toSubs);
    void removeNode(set<int> *set, int node);
    void addNode(set<int> *set, int node);
    set<int> createSet(vector<int> vector);
    void printSet(set<int> set);

};


#endif //PROJEKTAAL_LOGIC2_H
