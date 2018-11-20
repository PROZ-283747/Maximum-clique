//
// Created by adell.j on 20.11.2018.
//


#include <fstream>
#include <iomanip>
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
