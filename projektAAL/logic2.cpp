//
// Created by adell.j on 07.12.2018.
//

#include "logic2.h"

Logic2::Logic2(Graph *graph){
    cout<<"Konstruktor" << endl;
    myGraph = graph;
    maxCliqueSize = 0;
    numOfRecursion=0;
    maxClique.clear();
    R.clear();
    P.clear();
    X.clear();
}

Logic2::~Logic2() {}

void Logic2::initializeLogic2(int numOfNodes){
    maxCliqueSize = 0;
    maxClique.clear();
    R.clear();
    X.clear();
    fillInNodesToP(numOfNodes);
    numOfRecursion=0;
}

void Logic2::fillInNodesToP(int numOfNodes){
    for(int i=0; i <  myGraph->getNumberOfNodes(); ++i){
        P.insert(i);
    }
}
bool Logic2::isMaxBigger(set<int> R){
    cout<< "isMaxBigger"<<endl;
    if(R.size() <= maxClique.size())
        return true;
    return false;
}

void Logic2::setNewMaxClique(set<int> R){
    cout<< "setNewMaxClique"<<endl;
    maxClique.clear();
    maxClique.insert(R.begin(), R.end());
    maxCliqueSize = R.size();
}

set<int> Logic2::getUnion(set<int> A, set<int> B){
    cout<< "getUnion"<<endl;
    set<int> unionSet;
    auto itA = A.begin();
    auto itB = B.begin();
    if(A.empty())
        return B;
    if(B.empty())
        return A;
    while(itA != A.end() && itB != B.end()) {
        if (*itA < *itB) {
            unionSet.insert(*itA);
            ++itA;
        }
        if (*itA > *itB) {
            unionSet.insert(*itB);
            ++itB;
        }
        if(itA == A.end() && itB != B.end())
            unionSet.insert(*itB);
        if(itA != A.end() && itB == B.end())
            unionSet.insert(*itA);
    }
    return unionSet;
}

set<int> Logic2::getIntersection(set<int> A, set<int> B) {
    cout<< "getIntersection"<<endl;
    set<int> intersectionSet;
    auto itA = A.begin();
    auto itB = B.begin();
    while (itA != A.end() && itB != B.end()) {
        if (*itA == *itB) {
            intersectionSet.insert(*itA);
            ++itA;
            ++itB;
        } else {
            if (*itA > *itB)
                ++itB;
            if (*itA < *itB)
                ++itA;

        }
    }
    return intersectionSet;
}

set<int> Logic2::substractSet(set<int> setFrom, vector<int> toSubs) {
    for(auto it = toSubs.begin(); it != toSubs.end(); ++it) {
        setFrom.erase(*it);
    }
    return setFrom;
}

void Logic2::removeNode(set<int> *set, int node){
    set->erase(node);
}

void Logic2::addNode(set<int> *set, int node){
    set->insert(node);
}

set<int> Logic2::createSet(vector<int> vector){
    set<int> result;
    for(int i=0; i < vector.size(); ++i){
        result.insert(vector[i]);
    }
    return result;
}

int Logic2::findPivot(set<int> set) {
    cout << "findPivot" << endl;
    int pivot;
    int maxNCount = 0;
    // dla każdego wierzchołka w P"
    for (auto it = set.begin(); it != set.end(); ++it) {
        int neighbourtsCount = 0;
        int node = *it; // index in neighbours
        // count number of neighbours(belonging to set P) for every node from set
        for (int i = 0; i < myGraph->getNeighbours()[node].size(); ++i) {
            for (auto itP = set.begin(); itP != set.end(); ++itP) {
                if (myGraph->getNeighbours()[node][i] == *itP)
                    ++neighbourtsCount;
            }
        }
        if (neighbourtsCount >= maxNCount) {
            pivot = *it;   // set new pivot
            maxNCount = neighbourtsCount;
        }
    }
    return pivot;
}

void Logic2::printSet(set<int> set){
    for(auto it = set.begin(); it != set.end(); ++it){
        cout<< *it << " ";
    }
    cout<<endl;
}

void Logic2::printResult(){
    cout<<"MAXIMAL CLIQUE: "; printSet(maxClique);
    cout<< "SIZE: "<< maxCliqueSize<<endl;
    cout<< "Num of rec: "<< numOfRecursion<<endl;
}

const set<int> &Logic2::getP() const {
    return P;
}

const set<int> &Logic2::getR() const {
    return R;
}

const set<int> &Logic2::getX() const {
    return X;
}

void Logic2::setP(const set<int> &P) {
    Logic2::P = P;
}

void Logic2::setR(const set<int> &R) {
    Logic2::R = R;
}

void Logic2::setX(const set<int> &X) {
    Logic2::X = X;
}

void Logic2::findMaximalClique(set<int> R, set<int> P, set<int> X) {
    ++numOfRecursion;
    cout<<endl << "START" << endl;
    cout << "R: "; printSet(R);
    cout << "P: "; printSet(P);
    cout << "X: "; printSet(X);
    cout << "MAX: "; printSet(maxClique);
    set<int> newR;
    set<int> newP;
    set<int> newX;
    if (P.empty() && X.empty()) {
        if (!isMaxBigger(R))
            setNewMaxClique(R);
    }
    else {
        int pivot = findPivot(getUnion(P, X)); // sasiedzi zaw sie w P czy w P suma X ????
        cout << "Pivot: " << pivot << endl;
        set<int> withoutNeighbours = substractSet(P, myGraph->getNeighbours()[pivot]);
        cout << "Without neighbours: "; printSet(withoutNeighbours);

        for (auto it = withoutNeighbours.begin(); it != withoutNeighbours.end(); ++it) {
            cout<< "IT: "<< *it<<endl;
            cout<< "set: "; printSet(createSet(myGraph->getNeighbours()[*it]));
            newR.clear();
            newP.clear();
            newX.clear();
            newR.insert(R.begin(), R.end());
            newR.insert(*it);
            // addNode(&newR, *it);
            newP = getIntersection(P, createSet(myGraph->getNeighbours()[*it]));
            newX = getIntersection(X, createSet(myGraph->getNeighbours()[*it]));

            cout << "newR: "; printSet(newR);
            cout << "newP: "; printSet(newP);
            cout << "newX: "; printSet(newX);
            findMaximalClique(newR, newP, newX);
            //removeNode(&P, *it);
            //addNode(&X, *it);
        }
    }

}