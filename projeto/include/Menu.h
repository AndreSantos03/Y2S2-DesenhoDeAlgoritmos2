//
// Created by diogo on 29/05/2023.
//

#ifndef DA_PROJECT2_MENU_H
#define DA_PROJECT2_MENU_H

#include "information_management/ReadData.h"
#include "graph/Algorithms.h"
#include <string>
#include <sstream>



class Menu {
public:
    Menu();
    void display();
    void chooseGraphs();
    void setGraphNormalFile(const string &filename);
    void setGraphLargeFile(const string &filename);



private:
    Graph graph;
    ReadData data;
    Algorithms algorithms;

    void loadDataSet();
    void toyGraphs();
    void mediumGraphs();
    void realWorldGraphs();

    void backtracking_menu();
    void otherHeuristicsMenu();

    int cin_int();
};


#endif //DA_PROJECT2_MENU_H
