//
// Created by NASA on 25/05/2023.
//

#include <utility>

#include "../../include/graph/Algorithms.h"

Algorithms::Algorithms(Graph graph) : graph(std::move(graph)) {}



void Algorithms::setGraph(Graph graph_) {
    this->graph = std::move(graph_);
}


void Algorithms::setAllNonVisited() {
    for(auto v : graph.getVertexSet()){
        v->setVisited(false);
    }
}

double Algorithms::backtracking(Vertex* curr_vertex, std::vector<bool>& visited, int count, double weight, double min_weight, Vertex* start_vertex, std::vector<int>& min_path, std::vector<int>& curr_path) {
    visited[curr_vertex->getId()] = true;
    curr_path.push_back(curr_vertex->getId());
    count++;

    if (count == visited.size()) {
        for (Edge* edge : curr_vertex->getAdj()) {
            if (edge->getDest() == start_vertex) {
                double total_weight = weight + edge->getWeight();
                if (total_weight < min_weight) {
                    min_weight = total_weight;
                    min_path = curr_path;
                }
                break;
            }
        }
    } else {
        for (Edge* edge : curr_vertex->getAdj()) {
            Vertex* adj_vertex = edge->getDest();
            if (!visited[adj_vertex->getId()]) {
                double new_weight = weight + edge->getWeight();
                if (new_weight < min_weight) {
                    min_weight = backtracking(adj_vertex, visited, count, new_weight, min_weight, start_vertex, min_path, curr_path);
                }
            }
        }
    }

    visited[curr_vertex->getId()] = false;
    curr_path.pop_back();
    count--;

    return min_weight;
}


/*
vector<int> Algorithms::btLoop() {
    if(lab)
}
*/
