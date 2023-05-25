//
// Created by NASA on 25/05/2023.
//

#include "../../include/graph/Algorithms.h"

Algorithms::Algorithms(Graph graph) : graph(graph) {}



void Algorithms::setGraph(Graph graph) {
    this->graph = graph;
}

void Algorithms::setAllNonVisited() {
    for(auto v : graph.getVertexSet()){
        v->setVisited(false);
    }
}

vector<int> Algorithms::backtracking() {
    setAllNonVisited();
}

vector<int> Algorithms::btLoop() {
    if(lab)
}
