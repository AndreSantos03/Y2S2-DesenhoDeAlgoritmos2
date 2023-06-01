//
// Created by NASA on 25/05/2023.
//

#include <utility>
#include <queue>

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

    vector<vector<Vertex*>> clusters(numClusters);
    vector<vector<Vertex*>> clusterPaths(numClusters);

    vector<double> longitudes;
    vector<double> latitudes;

    //split into squares, the num of clusters must always be pair, prioritize longitude spacing as its values will vary mor
    int sectorsX = numClusters / 2;
    cout << "sectorsX: " << sectorsX << endl;
    int sectorsY = numClusters / sectorsY;
    cout << "sectorsY: " << sectorsX << endl;

    for(auto v : graph.getVertexSet()){
        longitudes.push_back(v->getLongitude());
        latitudes.push_back(v->getLatitude());
        v->setVisited(false);
    }
    sort(longitudes.begin(),longitudes.end());
    sort(latitudes.begin(),latitudes.end());

    double minLon = longitudes[numClusters];
    double minLat = latitudes[numClusters];

    cout << "minLon: " << minLon<< endl;
    cout << "minLat: " << minLat << endl;

    cout << "midlat: " << latitudes[numClusters/2] << endl;
    cout << "midlon: " << longitudes[numClusters/2] << endl;

    double clusterSizeLon = (longitudes[numClusters/2] - longitudes[0]) * 2 / sectorsY;
    cout << "clusterSizeLon: " << clusterSizeLon << endl;
    double clusterSizeLat = (latitudes[numClusters/2] - latitudes[0]) * 2 / sectorsX;
    cout << "clusterSizeLat: " << clusterSizeLat << endl;


    for (auto v : graph.getVertexSet()) {
        int clusterX = (v->getLongitude() - minLon) / clusterSizeLon;
        int clusterY =(v->getLatitude() - minLat) / clusterSizeLat;
        cout << " x: " << (v->getLongitude() - minLon) << endl;
        cout << " // " << clusterSizeLon << endl;
        cout << " y: " << (v->getLatitude() - minLat) << endl;
        cout << " // " << clusterSizeLat << endl;
        cout << "cluster x: " << clusterX << endl;
        cout << "cluster y: " << clusterY << endl;
        int clusterIndex = clusterY * sectorsX + clusterX - 1 ;
        cout << "cluster index: " << clusterIndex<< endl;
        clusters[clusterIndex].push_back(v);
    }

    for(auto c : clusters){
        cout << c.size() << "cluster size" << endl;
    }
    int count = 0;
    for(auto cluster : clusters){
        cout << "23231" << endl;
        clusterPaths[count].push_back(cluster[0]);
        cout << "434334" << endl;

        cluster[0]->setVisited(true);
        cout << "12321312" << endl;

        for(int i = 0; i<cluster.size()-1;i++){
            Vertex * nextVertex = findNearestVertexCluster(clusterPaths[count][i],cluster);
            clusterPaths[count].push_back(nextVertex);
            cluster.erase(find(cluster.begin(),cluster.end(),nextVertex));
            nextVertex->setVisited(true);
        }
        cout << "655757" << endl;

        count++;
    }
    cout << "3" << endl;

    for(auto cluster : clusters){
        path.insert(path.end(),cluster.begin(),cluster.end());
    }
    cout << "4" << endl;
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


