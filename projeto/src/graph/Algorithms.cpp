#include <utility>
#include <queue>

#include "../../include/graph/Algorithms.h"

Algorithms::Algorithms() = default;
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

double Algorithms::primMST() {
    for(auto &v : graph.getVertexSet()){
        v->setDist(std::numeric_limits<double>::max());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = graph.getVertexSet().front();
    s->setDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);


    double out = 0;

    while(!q.empty()){
        auto v = q.extractMin();
        if(v->getPath() != nullptr ) out += v->getPath()->getWeight()*2;
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return out;
}

Graph Algorithms::primMSTgraph() {
    for(auto &v : graph.getVertexSet()){
        v->setDist(std::numeric_limits<double>::max());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = graph.getVertexSet().front();
    s->setDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    Graph mstGraph;

    while(!q.empty()){
        auto v = q.extractMin();
        v->setVisited(true);

        if (v->getPath() != nullptr) {
            mstGraph.addEdge(v->getPath()->getOrig()->getId(), v->getPath()->getDest()->getId(), v->getPath()->getWeight());
            mstGraph.addEdge(v->getPath()->getDest()->getId(), v->getPath()->getOrig()->getId(), v->getPath()->getWeight());
        }

        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return mstGraph;
}

vector<Vertex*> Algorithms::christofidesTSP() {
    // 1. Calcula a MST usando o algoritmo de Prim
    Graph mst = primMSTgraph();
    // 2. Encontra os vértices com grau ímpar na MST
    vector<Vertex*> oddVertices;

    for (auto v : mst.getVertexSet()) {
        if (v->getAdj().size() % 2 != 0) {
            oddVertices.push_back(v);
        }
    }


    // 3. Constrói um subgrafo apenas com os vértices de grau ímpar
    Graph oddGraph;
    for (auto v : oddVertices) {
        for (auto e : v->getAdj()) { // Alteração: Iterar sobre as adjacências do vértice atual (v)
            if (find(oddVertices.begin(), oddVertices.end(), e->getDest()) != oddVertices.end()) {
                oddGraph.addEdge(e->getOrig()->getId(), e->getDest()->getId(), e->getWeight()); // Alteração: Passar o vértice de origem e destino diretamente
            }
        }
    }


    // 4. Encontra um caminho Euleriano na MST
    vector<Vertex*> mstPath = mst.findEulerianPath();

    // 5. Encontra um caminho Hamiltoniano no subgrafo com vértices de grau ímpar
    vector<Vertex*> oddPath = oddGraph.findHamiltonianPath();

    // 6. Combina os caminhos da MST e do subgrafo com vértices de grau ímpar
    vector<Vertex*> finalPath;
    for (auto v : mstPath) {
        finalPath.push_back(v);
    }
    for (auto v : oddPath) {
        finalPath.push_back(v);
    }

    double minDistance = 0;
    for (size_t i = 0; i < finalPath.size() - 1; i++) {
        Vertex* source = finalPath[i];
        Vertex* dest = finalPath[i + 1];
        double distance = calculateDistance(source, dest);
        minDistance += distance;
    }

    cout << endl << "The graph has a minimum distance of: " << minDistance << "." << endl;
    return finalPath;
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


