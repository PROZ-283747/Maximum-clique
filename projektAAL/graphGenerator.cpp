//
// Created by adell.j on 31.10.2018.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "graphGenerator.h"

// constructor to generate graph with given number of nodes, size od maximal clique and number of edges beside clique
GraphGenerator::GraphGenerator(int numOfNodes, int numOfEdges, int sizeOfBClique){
//  todo
//    if(numOfNodes*(numOfNodes-1)< sizeOfBClique*(sizeOfBClique-1) + numOfEdges)
//       throw "Inappropriate parameters to generate graph!";
    numberOfEdges = numOfEdges;
    numberOfNodes = numOfNodes;
    sizeOfBiggestClique = sizeOfBClique;
};

// constructor to generate full graph
GraphGenerator::GraphGenerator(int numOfNodes){
    numberOfNodes = numOfNodes;
    numberOfEdges = numOfNodes*(numOfNodes-1)/2;
    sizeOfBiggestClique = numOfNodes;
};

// constructor to generate graph which is path
GraphGenerator::GraphGenerator(int numOfNodes, int pathLength){
    numberOfNodes = numOfNodes;
    numberOfEdges = pathLength;
    sizeOfBiggestClique = 0;
};

// use to generate nodes to maximal clique
vector<int> GraphGenerator::generateNumbersWithoutRepetition(int number, int upperRange){
    vector<int> vector;
    while(vector.size() < number){
        int random =( rand() % upperRange );
        if(find(vector.begin(), vector.end(), random) != vector.end()){
            continue;
        }
        else
            vector.push_back(random);
    }
    return vector;
}

// check if node is in vector
bool GraphGenerator::isElementInVector(vector<int> vector, int element){
    find(vector.begin(), vector.end(), element) != vector.end();
}

// to generate edges beside the maximal clique; if particular egde have already existr it draws again
pair<int, int> GraphGenerator::generateVertice(vector<vector<int>> neighbours){
    pair<int, int> vertice;
    int vert1;
    int vert2;
    do {
        vert1 = rand() % numberOfNodes;
        vert2 = rand() % numberOfNodes;
        vertice.first = vert1;
        vertice.second = vert2;
    }while(verticeExists(vertice, neighbours) || vert1 == vert2);
    //cout<<"Vertice: "<< vertice.first << " "<< vertice.second<<endl;
    return vertice;
}

// checks if particular two nodes are connected
bool GraphGenerator::verticeExists(pair<int, int> vertic, vector<vector<int>> neighbours){
    return isElementInVector(neighbours[vertic.first], vertic.second);
}

//sets given clique to the graph
void GraphGenerator::setCliqueToGraph(vector<int> clique, vector<vector<int>> *neighbours){
    for(int i=0; i< clique.size(); ++i){
        int node = clique[i];
        for(int j=0; j< clique.size(); ++j){
            if(!isElementInVector((*neighbours)[clique[j]], node) && node != clique[j])
                (*neighbours)[clique[j]].push_back(node);
        }
    }
}


void GraphGenerator::setVerticeToGraph(pair<int, int> vertice, vector<vector<int>> *neighbours){
    if(!isElementInVector((*neighbours)[vertice.first], vertice.second))
        (*neighbours)[vertice.first].push_back(vertice.second);
    if(!isElementInVector((*neighbours)[vertice.second], vertice.first))
        (*neighbours)[vertice.second].push_back(vertice.first);
}

// puts empty vectors to neighbors, then they will be filled
void GraphGenerator::initializeAuxiliaryVector(vector<vector<int>> *neighbours){
    for(int i=0; i < numberOfNodes; ++i){
        neighbours->push_back({});
    }
}

// Generates graph, fills in graph's attributes while creating it and saves graph to file
pair<int, vector<vector<int>>> GraphGenerator::generateGraph(){
    cout<<"generate"<<endl;
    pair<int, vector<vector<int>>> graphParams; // first value is number of nodes and second are neighbours of nodes
    vector<vector<int>> neighbours;
    initializeAuxiliaryVector(&neighbours);
    vector<int> biggestClique = generateNumbersWithoutRepetition(sizeOfBiggestClique, numberOfNodes);
    setCliqueToGraph(biggestClique, &neighbours);

    // numOfEdges must be maximally equal to the difference between maximal number of edges in graph and number of edges in clique
        for (int i = 0; i < numberOfEdges; ++i) {
            setVerticeToGraph(generateVertice(neighbours), &neighbours);
        }

    fileManager->saveGraphToFile("../genGraph.txt", numberOfNodes, neighbours);
    graphParams.first = numberOfNodes; //assigns numberOfNodes given as an argument to the program to attribute in a class Graph.
    graphParams.second = neighbours;
    return graphParams;
}

pair<int, vector<vector<int>>> GraphGenerator::generateCompleteGraph(){
    cout<<"generateCompleteGraph"<<endl;
    pair<int, vector<vector<int>>> graphParams; // first value is number of nodes and second are neighbours of nodes
    vector<vector<int>> neighbours;
    vector<int> biggestClique;

    initializeAuxiliaryVector(&neighbours);
    for(int i=0; i< numberOfNodes; ++i){
        biggestClique.push_back(i);
    }
    setCliqueToGraph(biggestClique, &neighbours);

    fileManager->saveGraphToFile("../genGraph.txt", numberOfNodes, neighbours);
    graphParams.first = numberOfNodes; //assigns numberOfNodes given as an argument to the program to attribute in a class Graph.
    graphParams.second = neighbours;
    return graphParams;
}

pair<int, vector<vector<int>>> GraphGenerator::generatePathGraph(){
    cout<<"generateCompleteGraph"<<endl;
    pair<int, vector<vector<int>>> graphParams; // first value is number of nodes and second are neighbours of nodes
    vector<vector<int>> neighbours;
    vector<int> biggestClique;

    cout<< "number of nodes: "<< numberOfNodes <<endl;
    cout<< "number od edges: "<< numberOfEdges <<endl;

    for(int i =0; i<numberOfNodes; ++i){
        neighbours.push_back({});
    }

    for(int i=0; i < numberOfNodes; ++i){
        cout<< "i: " << i << endl;
        cout<< "i-1: " << i-1 << endl;
        cout<< "i+1: " << i+1 << endl;
        if(i-1 >= 0)
            neighbours[i].push_back(i-1);
        if(i+1 < numberOfNodes)
            neighbours[i].push_back(i+1);
    }


    fileManager->saveGraphToFile("../genGraph.txt", numberOfNodes, neighbours);
    graphParams.first = numberOfNodes; //assigns numberOfNodes given as an argument to the program to attribute in a class Graph.
    graphParams.second = neighbours;
    return graphParams;
}