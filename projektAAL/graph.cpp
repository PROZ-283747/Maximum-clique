/* 11th November 2018
 * Author: Adela Jaworowska
 * Project: Algorithm to find the biggest full subgraph in a graph with n nodes.
 */

#include <regex>
#include "graph.h"

//Graph::Graph() : numberOfNodes(0) {
  //  cout<< "OMG znowu ten konstruktor." <<endl;
//    neighbours.push_back({1, 2});
//    neighbours.push_back({0, 2});
//    neighbours.push_back({0, 1, 3});
//    neighbours.push_back({2});

//    neighbours.push_back({1, 2, 3});
//    neighbours.push_back({0, 2, 3});
//    neighbours.push_back({0, 1, 3});
//    neighbours.push_back({0, 1, 2});
//    neighbours.push_back({3});

//    neighbours.push_back({2});
//    neighbours.push_back({2});
//    neighbours.push_back({0, 1});
//    neighbours.push_back({});

//    neighbours.push_back({2});
//    neighbours.push_back({2});
//    neighbours.push_back({0, 1});
//    neighbours.push_back({});

//    neighbours.push_back({3});
//    neighbours.push_back({2, 4, 5, 7});
//    neighbours.push_back({1, 4, 5,7});
//    neighbours.push_back({0, 4, 6, 7});
//    neighbours.push_back({1, 2, 5, 7, 6, 3});
//    neighbours.push_back({1, 2, 4, 7});
//    neighbours.push_back({3, 4, 7});
//    neighbours.push_back({6, 3, 4, 1, 2, 5});
//    neighbours.push_back({});
//}

Graph::Graph(string fileName) {
    readGraphFromFile(fileName);
}

Graph::Graph(char* argv[]) {
    // generateGraph();
}

Graph::~Graph() {}

void Graph::setNumberOfNodes(int numOfNodes)
{
    numberOfNodes = numOfNodes;
}

void Graph::setNeighbours(vector<int> intVect){
    neighbours.push_back(intVect);
}

void Graph::printNeighbours(){
    for(int i=0; i<neighbours.size(); ++i){
        for(int j=0; j<neighbours[i].size(); ++j){
            cout << neighbours[i][j]<< " ";
        }
        cout<<endl;
    }
}

const vector<vector<int>> &Graph::getNeighbours() const {
    return neighbours;
}

vector<int> Graph::changeStringVectorToInts(vector<string> strVect){
    vector<int> intVect;
    for(int i=0; i< strVect.size(); ++i){
        intVect.push_back(stoi(strVect[i]));
    }
    return intVect;
}

int Graph::getNumberOfNodes() const {
    return numberOfNodes;
}

void Graph::readGraphFromFile(string fileName) {
    cout << "Read graph form console"<<endl;
    int numOfNodes=0;
    string neighboursOfOneNode;

    ifstream file;
    file.open("../" + fileName, ios::out);

    if(file) {
        file >> numOfNodes;
        setNumberOfNodes(numOfNodes);
        cout << "NumN: " << numOfNodes << endl;
        std::getline( file, neighboursOfOneNode ); // reads line with number of nodes
        while( !file.eof() ) /* Dopóki kursor nie znajdzie sie na koncu EOF - 'EndOfFile' */
        {
            for(int i=0; i <  numOfNodes; ++i) {
                std::getline(file, neighboursOfOneNode); /* Funkcja getline wczytuje caly wiersz do stringa */
                istringstream iss(neighboursOfOneNode);
                vector<string> neighbours((istream_iterator<string>(iss)), istream_iterator<string>());
                setNeighbours(changeStringVectorToInts(neighbours));
            }
        }
    }
    else{
        cout<<"Opening file failed."<<endl;
        return;
    }
    file.close();
}