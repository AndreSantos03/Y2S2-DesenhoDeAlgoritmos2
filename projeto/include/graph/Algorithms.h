//
// Created by NASA on 25/05/2023.
//

#ifndef DA_PROJECT2_ALGORITHMS_H
#define DA_PROJECT2_ALGORITHMS_H


#include "Graph.h"


using namespace std;


class Algorithms {
public:


    Algorithms(Graph graph);

    void setGraph(Graph graph);

    vector<int> backtracking();

private:

    vector<int> btLoop();
    void setAllNonVisited();

    Graph graph;
};


#endif //DA_PROJECT2_ALGORITHMS_H
