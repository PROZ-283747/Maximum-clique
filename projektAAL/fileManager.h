//
// Created by adell.j on 20.11.2018.
//

#ifndef PROJEKTAAL_FILEMANAGER_H
#define PROJEKTAAL_FILEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "graph.h"

using namespace std;

class FileManager {
public:
    void saveResultToFile(string fileName, int numOfNodes, float time);
    void saveGraphToFile(string fileName, int numOfNodes, vector<vector<int>> graph);
    void readGraphFromFile(string fileName, Graph *myGraph);
    vector<int> changeStringVectorToInts(vector<string> strVect);
};


#endif //PROJEKTAAL_FILEMANAGER_H
