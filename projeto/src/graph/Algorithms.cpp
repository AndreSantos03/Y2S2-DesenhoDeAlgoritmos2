//
// Created by NASA on 25/05/2023.
//

#include <utility>

#include "../../include/graph/Algorithms.h"

Algorithms::Algorithms() {}
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

vector<Vertex *> Algorithms::clusterBasedAlgorithm(int numClusters) {
    vector<Vertex *> path;
    int n = graph.getNumVertex();
    vector<vector<Vertex*>> clusters;
    vector<vector<Vertex*>> clusterPaths;

    Vertex* firstVertex = graph.findVertex(0);
    double minX = firstVertex->getLatitude(), maxX = firstVertex->getLatitude();
    double minY = firstVertex->getLongitude(), maxY = firstVertex->getLongitude();

    for(auto v : graph.getVertexSet()){
        if (v->getLatitude() < minX)
            minX = v->getLatitude();
        if (v->getLatitude() > maxX)
            maxX = v->getLatitude();
        if (v->getLongitude() < minY)
            minY = v->getLongitude();
        if (v->getLongitude() > maxY)
            maxY = v->getLongitude();

        v->setVisited(false);
    }

    double clusterSizeX = (maxX - minX) / numClusters;
    double clusterSizeY = (maxY - minY) / numClusters;

    for (auto v : graph.getVertexSet()) {
        int clusterX = floor((v->getLatitude() - minX) / clusterSizeX);
        int clusterY = floor((v->getLongitude() - minY) / clusterSizeY);
        int clusterIndex = clusterY * numClusters + clusterX;
        clusters[clusterIndex].push_back(v);
    }
    int count = 0;
    for(auto cluster : clusters){
        clusterPaths[count].push_back(cluster[0]);
        cluster[0]->setVisited(true);
        for(int i = 0; i<cluster.size()-1;i++){
            Vertex * nextVertex = findNearestVertexCluster(clusterPaths[count][i],cluster);
            clusterPaths[count].push_back(nextVertex);
            cluster.erase(find(cluster.begin(),cluster.end(),nextVertex));
            nextVertex->setVisited(true);
        }
        count++;
    }

    for(auto cluster : clusters){
        path.insert(path.end(),cluster.begin(),cluster.end());
    }
    return path;
}



double Algorithms::calculatePathCost(vector<Vertex *> path) {
    double cost = 0;
    for(int  i = 0; i < path.size()-1;i++){
        cost += path[i]->getEdge(path[i+1])->getWeight();
    }
    return cost;
}

double Algorithms::calculateDistance(Vertex *source, Vertex *dest) {
    double lat1 = source->getLatitude();
    double lat2 = dest->getLatitude();
    double lon1 = source->getLongitude();
    double lon2 = dest->getLongitude();

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

Vertex *Algorithms::findNearestVertexCluster(Vertex *current, vector<Vertex *> cluster) {
    Vertex* nearest;
    double dist = numeric_limits<double>::max();
    for(auto e : current->getAdj()){
        if(e->getWeight() < dist && find(cluster.begin(),cluster.end(),e->getDest()) != cluster.end()){
            nearest = e->getDest();
            dist = e->getWeight();
        }
    }

    return nearest;
}


