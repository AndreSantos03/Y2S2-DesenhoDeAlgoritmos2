//
// Created by NASA on 25/05/2023.
//

#ifndef DA_PROJECT2_ALGORITHMS_H
#define DA_PROJECT2_ALGORITHMS_H


#include "Graph.h"
#include "VertexEdge.h"
#include <xmath.h>
#include "MutablePriorityQueue.h"


using namespace std;


class Algorithms {
public:


    explicit Algorithms(Graph graph);

    void setGraph(Graph graph_);

    void backtracking(std::vector<int>& path, std::vector<bool>& visited, double &min_cost, double cost_so_far);

    void primMST(Graph graph);

    int minKey(int key[], bool mstSet[]);

    int printMST(int parent[], Graph graph);

    double dfs(Vertex* vertex);

private:

    vector<int> btLoop();
    void setAllNonVisited();

    Graph graph;

    std::vector<Vertex *> MST;
};


#endif //DA_PROJECT2_ALGORITHMS_H
