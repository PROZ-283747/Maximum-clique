//
// Created by adell.j on 20.11.2018.
//

#ifndef PROJEKTAAL_FILEMANAGER_H
#define PROJEKTAAL_FILEMANAGER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class FileManager {
public:
    void saveResultToFile(string fileName, int numOfNodes, float time);
    void saveGraphToFile(string fileName, int numOfNodes, vector<vector<int>> graph);
};


#endif //PROJEKTAAL_FILEMANAGER_H
