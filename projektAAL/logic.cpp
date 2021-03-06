/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */
#include <regex>
#include "logic.h"


Logic::Logic(Graph *graph) : rmsize(0) {
    cout<<"To ma sie wywolywac" << endl;
    myGraph = graph;
    partialResult.clear();
    skippedNodes.clear();
    nodesToConsider.clear();
}

Logic::~Logic() {}

void Logic::initializeNodesToConsiderVect(int numberOfNodes){
    for(int i=0; i< numberOfNodes; ++i){
        nodesToConsider.push_back(i);
    }
};
void Logic::assignVectorToVector(vector<int>* vect1, vector<int> vect2){
    vect1->assign(vect2.begin(), vect2.end());
}

vector<int> Logic::productOfTwoVectors(vector<int> vect1, vector<int> vect2){
    vector<int> vector;
    for(int i=0; i<vect1.size(); ++i){
        if(isElementInVector(vect2, vect1[i]))
            vector.push_back(vect1[i]);
    }
    return vector;
}

bool Logic::isElementInVector(vector<int> vector, int element){
    find(vector.begin(), vector.end(), element) != vector.end();
}

int Logic::findPositionOfElementInVector(vector<int> vector, int element){
    for(int i=0; i< vector.size(); ++i){
        if(vector[i] ==  element)
            return i;
    }
    return -1;
}

void Logic::removeElementFromVector(vector<int>* vector, int element){
    if(isElementInVector(*vector, element)) {
        vector->erase(vector->begin() + findPositionOfElementInVector(*vector, element));
    }
    return;
}

void Logic::printVector(vector<int> vector){
    for(int i=0; i< vector.size(); ++i){
        cout<< vector[i] << " ";
    }
    cout<<endl;
}

vector<int> Logic::changeStringVectorToInts(vector<string> strVect){
    vector<int> intVect;
    for(int i=0; i< strVect.size(); ++i){
        intVect.push_back(stoi(strVect[i]));
    }
    return intVect;
}

void Logic::readGraphFromFile(string fileName) {
    cout << "Read graph form console"<<endl;
    int numOfNodes=0;
    string neighboursOfOneNode;

    ifstream file;
    file.open("../" + fileName, ios::out);

    if(file) {
        file >> numOfNodes;
        myGraph->setNumberOfNodes(numOfNodes);
        cout << "NumN: " << numOfNodes << endl;
        std::getline( file, neighboursOfOneNode ); // reads line with number of nodes
        while( !file.eof() ) /* Dopóki kursor nie znajdzie sie na koncu EOF - 'EndOfFile' */
        {
            for(int i=0; i <  numOfNodes; ++i) {
                std::getline(file, neighboursOfOneNode); /* Funkcja getline wczytuje caly wiersz do stringa */
                istringstream iss(neighboursOfOneNode);
                vector<string> neighbours((istream_iterator<string>(iss)), istream_iterator<string>());
                myGraph->setNeighbours(changeStringVectorToInts(neighbours));
            }
        }
    }
    else{
        cout<<"Opening file failed."<<endl;
        return;
    }
    file.close();
}

vector<int> Logic::findBiggestClique(Graph *graph, vector<int> partialResult, vector<int> nodesToConsider, int rmsize){
    cout<<"Find biggest clique"<<endl;
    cout<<"Nodes to consider: "; printVector(nodesToConsider);
    cout<<"Partial result: "; printVector(partialResult);
    cout<<"skippedNodes: "; printVector(skippedNodes);

    vector<int> nodesToConsiderPrimP;
    vector<int> nodesToConsiderBisP;
    vector<int> partialResultPrimR;
    //vector<int> skippedNodesPrimX;
    vector<int> tempNodesN;
    vector<int> biggestCliqueRM;
    int u=0, v=0, w=0, ncmax=0, nc=0, rms=0;

    if(nodesToConsider.empty()){//&& skippedNodes.empty()){
        rms = partialResult.size();
        if(rms > rmsize){
            biggestCliqueRM.assign(partialResult.begin(), partialResult.end());
            rmsize = rms;
        }
        cout<<"BIGGEST: ";
        printVector(biggestCliqueRM);
        cout<<"SIZE: "<< rmsize<<endl;
        return biggestCliqueRM;
    }
    else {
        cout<<"ELSE"<<endl;
        nodesToConsiderBisP.clear();
        cout<<"Nodes to consider Bis: ";  printVector(nodesToConsiderBisP);
        for (int i = 0; i < nodesToConsider.size(); ++i) {

            nodesToConsiderBisP.push_back(nodesToConsider[i]);
        }
        for (int i = 0; i < skippedNodes.size(); ++i) {
            nodesToConsiderBisP.push_back(skippedNodes[i]);
        }
        cout<<"Nodes to consider Bis <- P i X: ";  printVector(nodesToConsiderBisP);
        ncmax = 0;
        // dla każdego wierzchołka w P"
        for(int i =0; i< nodesToConsiderBisP.size(); ++i){
            nc = 0;
            u = nodesToConsiderBisP[i]; // wierzchołek z P" - indeks w neighbours

            // dla każdego sąsiada wierzchołka u z P"
            for(int j =0; j< myGraph->getNeighbours()[u].size(); ++j){
                for(int k=0; k< nodesToConsider.size(); ++k){
                    if (myGraph->getNeighbours()[u][j] == nodesToConsider[k])
                        nc++;
                }}
                if(nc >= ncmax){
                    v = u;   // piwot
                    ncmax = nc;
                }
            }
            nodesToConsiderBisP.assign(nodesToConsider.begin(), nodesToConsider.end());
            cout<<"Nodes to consider Bis <- P: ";  printVector(nodesToConsiderBisP);
            for(int i=0; i < myGraph->getNeighbours()[v].size(); ++i) {
                removeElementFromVector(&nodesToConsiderBisP, myGraph->getNeighbours()[v][i]);
            }
            cout<<"v: "<< v<<endl;
            cout<<"Nodes to consider Bis bez sasiadow: ";  printVector(nodesToConsiderBisP);
                tempNodesN.clear();

                  for(int j=0; j<myGraph->getNeighbours()[v].size(); ++j) {
                        tempNodesN.push_back(myGraph->getNeighbours()[v][j]);
                  }
                    cout<<"N z sasiadami: ";  printVector(tempNodesN);
                partialResultPrimR.assign(partialResult.begin(), partialResult.end());
                partialResultPrimR.push_back(v);
                    cout<<"R': ";  printVector(partialResultPrimR);
                assignVectorToVector(&nodesToConsiderPrimP, productOfTwoVectors(nodesToConsider, tempNodesN));
                    cout<<"P n N : ";  printVector(productOfTwoVectors(nodesToConsider, tempNodesN));
                    cout<<"P': ";  printVector(nodesToConsiderPrimP);
                    //assignVectorToVector(&skippedNodesPrimX, productOfTwoVectors(skippedNodes, tempNodesN));
                    cout<<"X n N : ";  printVector(productOfTwoVectors(skippedNodes, tempNodesN));
                    //cout<<"X': ";  printVector(skippedNodesPrimX);

                    //findBiggestClique(graph, partialResultPrimR, nodesToConsiderPrimP, skippedNodesPrimX, rmsize);
                    cout<<"Partial: "; printVector(partialResult); cout<<endl;
                    cout<<"N T C: "; printVector(nodesToConsider); cout<<endl;

                findBiggestClique(graph, partialResultPrimR, nodesToConsiderPrimP, rmsize);
            }
            cout<<"GMREKNGLKSNGK"<<endl;
            removeElementFromVector(&nodesToConsider,  v);  // P
            partialResult.push_back(v);                     // R
            cout<<"Partial: "; printVector(partialResult); cout<<endl;
            cout<<"N T C: "; printVector(nodesToConsider); cout<<endl;
    }


const vector<int> &Logic::getNodesToConsider() const {
    return nodesToConsider;
}

const vector<int> &Logic::getPartialResult() const {
    return partialResult;
}

const vector<int> &Logic::getSkippedNodes() const {
    return skippedNodes;
}

const int &Logic::getRmsize() const {
    return rmsize;
}

void Logic::setPartialResult(const vector<int> &partialResult) {
    Logic::partialResult = partialResult;
}

void Logic::setSkippedNodes(const vector<int> &skippedNodes) {
    Logic::skippedNodes = skippedNodes;
}



