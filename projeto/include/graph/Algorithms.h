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
    void setAllNonVisited();

    double backtracking(Vertex *curr_vertex, std::vector<bool> &visited, int count, double weight, double min_weight, Vertex *start_vertex, std::vector<int> &min_path, std::vector<int> &curr_path);

    vector<Vertex *> clusterBasedAlgorithm(int numClusters);

private:
    double calculatePathCost(vector<Vertex*> path);
    double calculateDistance(Vertex* source, Vertex* dest);
    Vertex* findNearestVertexCluster(Vertex* current,vector<Vertex*> cluster);
    vector<int> btLoop();


    Graph graph;
};


#endif //DA_PROJECT2_ALGORITHMS_H
