/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include "graphGenerator.h"

// constructor to generate graph with given number of nodes, size of maximal clique and number of edges beside clique
GraphGenerator::GraphGenerator(int numOfNodes, int numOfEdges, int sizeOfBClique){

    // Checks if data is correct. If no - returns communicate and exits program.
    if(numOfNodes*(numOfNodes-1)/2 < sizeOfBClique*(sizeOfBClique-1) + numOfEdges){
        std::cout<<"ERROR: Incorrect input data! Impossible to create graph of: ";
        std::cout<<numOfNodes<<" nodes, max clique of size: "<<sizeOfBClique<<" and "<<numOfEdges<<" edges beside clique."<<std::endl;
        exit(-1);
    }
    numberOfEdges = numOfEdges;
    numberOfNodes = numOfNodes;
    sizeOfBiggestClique = sizeOfBClique;
};

// Generates nodes to maximal clique
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

// Checks if node is already in vector
bool GraphGenerator::isElementInVector(vector<int> vector, int element){
    return vector.end() != find(vector.begin(), vector.end(), element); // dodałam return
}

// Generates edges beside the maximal clique; if particular edge have already exist it draws again
pair<int, int> GraphGenerator::generateEdge(vector<vector<int>> neighbours){
    pair<int, int> edge;
    int edge1;
    int edge2;
    do {
        edge1 = rand() % numberOfNodes;
        edge2 = rand() % numberOfNodes;
        edge.first = edge1;
        edge.second = edge2;
    }while(edgeExists(edge, neighbours) || edge1 == edge2);
    return edge;
}

// Checks if particular two nodes are connected.
bool GraphGenerator::edgeExists(pair<int, int> edge, vector<vector<int>> neighbours){
    return isElementInVector(neighbours[edge.first], edge.second);
}

// Sets given clique to the graph.
void GraphGenerator::setCliqueToGraph(vector<int> clique, vector<vector<int>> *neighbours){
    for(int i=0; i< clique.size(); ++i){
        int node = clique[i];
        for(int j=0; j< clique.size(); ++j){
            if(!isElementInVector((*neighbours)[clique[j]], node) && node != clique[j])
                (*neighbours)[clique[j]].push_back(node);
        }
    }
}

// Sets edges to graph.
void GraphGenerator::setEdgeToGraph(pair<int, int> edge, vector<vector<int>> *neighbours){
    if(!isElementInVector((*neighbours)[edge.first], edge.second))
        (*neighbours)[edge.first].push_back(edge.second);
    if(!isElementInVector((*neighbours)[edge.second], edge.first))
        (*neighbours)[edge.second].push_back(edge.first);
}

// Puts empty vectors to neighbors, they are filled later.
void GraphGenerator::initializeAuxiliaryVector(vector<vector<int>> *neighbours){
    for(int i=0; i < numberOfNodes; ++i){
        neighbours->push_back({});
    }
}

// Generates graph.
pair<int, vector<vector<int>>> GraphGenerator::generateGraph(){
    pair<int, vector<vector<int>>> graphParams; // first value is number of nodes and second are neighbours of nodes
    vector<vector<int>> neighbours;
    initializeAuxiliaryVector(&neighbours);
    vector<int> biggestClique = generateNumbersWithoutRepetition(sizeOfBiggestClique, numberOfNodes);
    setCliqueToGraph(biggestClique, &neighbours);

        for (int i = 0; i < numberOfEdges; ++i) {
            setEdgeToGraph(generateEdge(neighbours), &neighbours);
        }
    graphParams.first = numberOfNodes;
    graphParams.second = neighbours;
    return graphParams; // generated graph is later pass to setGraph() function from Graph class
}


