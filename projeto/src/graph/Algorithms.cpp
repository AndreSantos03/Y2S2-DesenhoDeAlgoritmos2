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

void Algorithms::backtracking(std::vector<int>& path, std::vector<bool>& visited, double& min_cost, double cost_so_far) {
    // Base case: if all vertices have been visited, check if the current cycle is a Hamiltonian cycle
    if (path.size() == graph.getNumVertex()) {
        // Check if the last vertex is adjacent to the starting vertex
        int start_vertex = path.front();
        int last_vertex = path.back();
        for (auto edge : graph.findVertex(last_vertex)->getAdj()) {
            if (edge->getDest() == graph.findVertex(start_vertex)) {
                // If it is, this is a Hamiltonian cycle; update the minimum cost if necessary
                double cycle_cost = cost_so_far + edge->getWeight();
                if (cycle_cost < min_cost) {
                    min_cost = cycle_cost;
                }
                break;
            }
        }
        return;
    }

    // Recursively consider all unvisited neighbors of the last vertex in the current path
    int last_vertex = path.back();
    for (auto edge : graph.findVertex(last_vertex)->getAdj()) {
        int next_vertex = edge->getDest()->getId();
        if (!visited[next_vertex]) {
            // Add the next vertex to the current path
            path.push_back(next_vertex);
            visited[next_vertex] = true;
            // Recursively explore the updated path
            backtracking(path, visited, min_cost, cost_so_far + edge->getWeight());
            // Remove the last vertex from the path and mark it as unvisited for the next iteration
            path.pop_back();
            visited[next_vertex] = false;
        }
    }
}


/*
vector<int> Algorithms::btLoop() {
    if(lab)
}
*/
