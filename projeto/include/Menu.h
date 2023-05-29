//
// Created by diogo on 29/05/2023.
//

#ifndef DA_PROJECT2_MENU_H
#define DA_PROJECT2_MENU_H

#include "information_management/ReadData.h"
#include "graph/Algorithms.h"



class Menu {
public:
    Menu();
    void display();

private:
    Graph graph;
    ReadData data;
    Algorithms algorithms;

    void loadDataSet();
};


#endif //DA_PROJECT2_MENU_H
