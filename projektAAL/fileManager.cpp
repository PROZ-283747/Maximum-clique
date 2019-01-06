/* January 2019
 * Author: Adela Jaworowska / indeks: 283747 / 283747@pw.edu.pl
 * Project: Finding maximal clique in a graph.
 */


#include <fstream>
#include <iomanip>
#include <regex>
#include "fileManager.h"


void FileManager::saveResultToFile(string fileName, int numOfNodes, float time){
    cout<<"vhjdtgfxhsfdxbg";
    ofstream outputFile;
    outputFile.open(fileName, ios::app );
    if (outputFile.is_open())
    {
        outputFile << numOfNodes << "   " << time << "\n";
    }
    else
        cout << "Saving to file failed.";
    outputFile.close();
}

void FileManager::saveGraphToFile(string fileName, int numOfNodes, vector<vector<int>> graph){
    ofstream outputFile;
    outputFile.open(fileName, ios::out| ios::trunc);
    if (outputFile.is_open())
    {
        outputFile << numOfNodes;
        outputFile << "\n";
        for(int i=0; i< numOfNodes; ++i){
            for(int j=0; j< graph[i].size(); ++j) {
                if(j== graph[i].size()-1)
                    outputFile << graph[i][j]; // There cannot be any white char behind the last node(neighbour) in a line.
                else
                    outputFile << graph[i][j] << " ";
            }
            if(i<numOfNodes-1) //There cannot be a new line behind neighbours of the last node in a graph.
                outputFile << "\n";
        }
    }
    else
        cout << "Saving to file failed.";
    outputFile.close();
}

vector<int> FileManager::changeStringVectorToInts(vector<string> strVect){
    vector<int> intVect;
    for(int i=0; i< strVect.size(); ++i){
        intVect.push_back(stoi(strVect[i]));
    }
    return intVect;
}

void FileManager::readGraphFromFile(string fileName, Graph *myGraph) {
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