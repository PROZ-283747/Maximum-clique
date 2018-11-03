//
// Created by adell.j on 01.11.2018.
//

#include <iostream>
#include "interface.h"

using namespace std;

Interface::Interface() {
    myGraph = new Graph();
    logic = Logic(myGraph);
}

Interface::~Interface() {
    delete myGraph;
}

void Interface::printOptions() {
    cout<<"This program can be used to find the biggest clique in a graph" <<endl;
    cout<<"\n************** MENU **************\n"
        <<"Choose one option to run program:\n"
        <<"1 - Enter the graph from console\n"
        <<"2 - Generate graph\n"
        <<"3 - Generate graph and do complex calculation\n" <<endl;
}
void Interface::readGraphFromConsole() {
    cout<<"Enter number of nodes: ";
    int numberOfNodes;
    int first, second;
    std::cin >> numberOfNodes;
    myGraph->setNumberOfNodes(numberOfNodes);
    myGraph->printNumberOfNodes();
    myGraph->setZerosToMarix();
    myGraph->printAdjecencyMatrix();
    cout<<endl<<"Enter edges: "<<endl;
    /*while(std::cin >> first >> second)
    {
        myGraph.setAdjecencyMatrix(first, second);
    }*/
    for(int i=0; i<7; ++i){
        std::cin >> first >> second;
        myGraph->setAdjecencyMatrix(first, second);
    }
    myGraph->printAdjecencyMatrix();
    cout<<"juz po"<<endl;
}

void Interface::menu() {
    int choice = 0;

    while(choice != 4){
        printOptions();
        cin >> choice;
        switch (choice) {
            case 1:
                cout<<"case 1"<<endl;
                readGraphFromConsole();
                myGraph->printAdjecencyMatrix();
                logic.addNodesToCandidatesList();
                logic.findBiggestClique(myGraph, logic.getPartialResult(), logic.getNodesToConsider(), logic.getSkippedNodes());
                break;
            case 2:
                cout<<"case 2"<<endl;
                break;
            case 3:
                cout<<"case 3"<<endl;
                break;
            case 4:
                cout<<"case 4"<<endl;
                return;
            default:
                break;
        }
    }
}