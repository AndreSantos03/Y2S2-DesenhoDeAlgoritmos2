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

void Algorithms::primMST(Graph graph) {
    for(auto v : graph.getVertexSet()){
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = graph.getVertexSet().front();
    s->setDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while(!q.empty()){
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
}

double Algorithms::dfs(Vertex* vertex) {
    cout << vertex->getId() << " ";

    double total = vertex->getPath()->getWeight();

    for (auto& e : vertex->getAdj()) {
        if(e->getDest()->getPath() != e) continue;
        total += dfs(e->getDest());
    }
    return total;
}

/*
vector<int> Algorithms::btLoop() {
    if(lab)
}
*/
