//
// Created by NASA on 25/05/2023.
//

#ifndef DA_PROJECT2_ALGORITHMS_H
#define DA_PROJECT2_ALGORITHMS_H


#include "Graph.h"
#include "VertexEdge.h"
#include <algorithm>
#include <cmath>



using namespace std;


class Algorithms {
public:

    Algorithms();

    explicit Algorithms(Graph graph);

    void setGraph(Graph graph_);

    void backtracking(std::vector<int>& path, std::vector<bool>& visited, double &min_cost, double cost_so_far);

    vector<Vertex *> clusterBasedAlgorithm(int numClusters);

private:
    double calculatePathCost(vector<Vertex*> path);
    double calculateDistance(Vertex* source, Vertex* dest);
    Vertex* findNearestVertexCluster(Vertex* current,vector<Vertex*> cluster);
    void setAllNonVisited();

    Graph graph;
};


#endif //DA_PROJECT2_ALGORITHMS_H
