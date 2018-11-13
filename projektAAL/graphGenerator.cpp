//
// Created by adell.j on 31.10.2018.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "graphGenerator.h"

GraphGenerator::GraphGenerator(int numOfNodes, int numOfEdges, int sizeOfBClique){
    numberOfEdges = numOfEdges;
    numberOfNodes = numOfNodes;
    sizeOfBiggestClique = sizeOfBClique;
};

vector<int> GraphGenerator::generateNumbersWithoutRepetition(int number, int upperRange){
    srand( time( NULL ) );
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

void GraphGenerator::saveGraphToFile(string fileName, vector<vector<int>> graph){
    ofstream outputFile;
    outputFile.open(fileName, ios::out| ios::trunc);
    if (outputFile.is_open())
    {
        outputFile << numberOfNodes;
        outputFile << "\n";
        for(int i=0; i< numberOfNodes; ++i){
            for(int j=0; j< graph[i].size(); ++j) {
                if(j== graph[i].size()-1)
                    outputFile << graph[i][j]; // There cannot be any white char behind the last node(neighbour) in a line.
                else
                    outputFile << graph[i][j] << " ";
            }
            if(i<numberOfNodes-1) //There cannot be a new line behind neighbours of the last node ina graph.
                outputFile << "\n";
        }
    }
    else
        cout << "Saving to file failed.";
    outputFile.close();
}

bool GraphGenerator::isElementInVector(vector<int> vector, int element){
    find(vector.begin(), vector.end(), element) != vector.end();
}

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
    cout<<"Vertice: "<< vertice.first << " "<< vertice.second<<endl;
    return vertice;
}

bool GraphGenerator::verticeExists(pair<int, int> vertic, vector<vector<int>> neighbours){
    return isElementInVector(neighbours[vertic.first], vertic.second);
}

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

void GraphGenerator::initializeAuxiliaryVector(vector<vector<int>> *neighbours){
    for(int i=0; i < numberOfNodes; ++i){
        neighbours->push_back({});
    }
}

// Generates graph, fills in graph's attributes while creating it and saves graph to file
pair<int, vector<vector<int>>> GraphGenerator::generateGraph(){
    cout<<"generate"<<endl;
    pair<int, vector<vector<int>>> graphParams; // first value is number od nodes and second neighbours of nodes
    vector<vector<int>> neighbours;
    initializeAuxiliaryVector(&neighbours);

    graphParams.first = numberOfNodes; //assigns numberOfNodes given as an argument to the program to attribute in a class Graph.
    vector<int> biggestClique = generateNumbersWithoutRepetition(sizeOfBiggestClique, numberOfNodes);
    setCliqueToGraph(biggestClique, &neighbours);
    for(int j=0; j<biggestClique.size(); ++j){
        cout << "Q: " << biggestClique[j]<<endl;
    }
    int numOfVerticesToAdd = numberOfEdges - (sizeOfBiggestClique*(sizeOfBiggestClique -1))/2;
    for(int i=0; i < numOfVerticesToAdd; ++i){
        setVerticeToGraph(generateVertice(neighbours), &neighbours);
        cout<<"**********"<<endl;
        for(int i=0; i<neighbours.size(); ++i){
            for(int j=0; j<neighbours[i].size(); ++j){
                cout << neighbours[i][j]<< " ";
            }
            cout<<endl;
        }
    }

    saveGraphToFile("../genGraph.txt", neighbours);
    for(int i=0; i<neighbours.size(); ++i){
        for(int j=0; j<neighbours[i].size(); ++j){
            cout << neighbours[i][j]<< " ";
        }
        cout<<endl;
    }
    return graphParams;
}