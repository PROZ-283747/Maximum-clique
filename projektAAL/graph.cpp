/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */


#include <regex>
#include "graph.h"

Graph::Graph() : numberOfNodes(0) {
    cout<<"Konstruktor grafu"<<endl;
}

Graph::~Graph() {}

void Graph::setNumberOfNodes(int numOfNodes) {
    numberOfNodes = numOfNodes;
}

void Graph::setNeighbours(vector<int> intVect){
    neighbours.push_back(intVect);
}

void Graph::printNeighbours(){
    cout<<"Print neighbours"<<endl;
    cout<<"**** "<< numberOfNodes<<" ****"<<endl;
    for(int i=0; i<neighbours.size(); ++i){
        for(int j=0; j<neighbours[i].size(); ++j){
            cout << neighbours[i][j]<< " ";
        }
        cout<<endl;
    }
    cout<<"********"<<endl;
}

const vector<vector<int>> &Graph::getNeighbours() const {
    return neighbours;
}

int Graph::getNumberOfNodes() const {
    return numberOfNodes;
}

void Graph::setGraph(pair<int , vector<vector<int>>> graphParams){
    numberOfNodes = graphParams.first;
    for(int i=0; i<numberOfNodes; ++i){
        neighbours.clear();
    }
    for(int i=0; i<numberOfNodes; ++i){
        neighbours.push_back(graphParams.second[i]);
    }
}

