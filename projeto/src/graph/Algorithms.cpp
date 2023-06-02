#include <utility>
#include <queue>
#include <unordered_set>

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

    vector<vector<Vertex*>> clusters(numClusters);
    vector<vector<Vertex*>> clusterPaths(numClusters);

    vector<Vertex*> auxVec(graph.getVertexSet());

    int n = auxVec.size();

    sort(auxVec.begin(),auxVec.end(),[](Vertex* a, Vertex* b) ->bool
    {return a->getLongitude()>b->getLongitude();});

    for(auto i = 0; i < numClusters ;i++){
        clusters[i].insert(clusters[i].begin(), auxVec.begin() + n/numClusters*i , auxVec.begin() + n/numClusters*(i+1));
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
    // Cria um novo grafo para a MST
    Graph mstGraph;

    // Verifica se o grafo original é vazio
    if (graph.isEmpty()) {
        return mstGraph; // Retorna um grafo vazio
    }

    // Mapeia os vértices do grafo original para os vértices da MST
    unordered_map<int, Vertex*> vertexMap;

    // Inicializa os vértices do grafo original e adiciona ao mstGraph
    for (auto& v : graph.getVertexSet()) {
        Vertex* newVertex = new Vertex(v->getId());
        mstGraph.addVertex(newVertex);
        vertexMap[v->getId()] = newVertex;

        v->setDist(std::numeric_limits<double>::max());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    // Seleciona o primeiro vértice como raiz
    Vertex* s = graph.getVertexSet().front();
    s->setDist(0);

    // Fila de prioridade para os vértices a serem processados
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);

        if (v->getPath() != nullptr) {
            // Obtém os vértices de origem e destino da aresta
            int origId = v->getPath()->getOrig()->getId();
            int destId = v->getPath()->getDest()->getId();

            // Adiciona os vértices correspondentes ao mstGraph
            mstGraph.addVertex(vertexMap[origId]);
            mstGraph.addVertex(vertexMap[destId]);

            // Adiciona a aresta ao grafo MST
            mstGraph.addEdge(origId, destId, v->getPath()->getWeight());
        }

        for (auto& e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if (e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    } else {
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
    unordered_set<int> oddVertexIds;

// Adicionar os vértices ímpares ao oddGraph
    for (auto v : oddVertices) {
        oddGraph.addVertex(v->getId());
        oddVertexIds.insert(v->getId());
    }

// Adicionar as arestas aos vértices ímpares no oddGraph
    for (auto v : oddVertices) {
        for (auto e : v->getAdj()) {
            if (oddVertexIds.count(e->getDest()->getId()) > 0) {
                oddGraph.addEdge(e->getOrig()->getId(), e->getDest()->getId(), e->getWeight());
            }
        }
    }



    // 4. Encontra um caminho Euleriano na MST
    vector<Vertex*> mstPath = mst.findEulerianPath();
    if(mstPath.empty()) cout << "test3" <<endl;
    else{
        cout << "test4" <<endl;
        for(auto v : mstPath){
            cout << v->getId() << endl;
        }
    }


    // 5. Encontra um caminho Hamiltoniano no subgrafo com vértices de grau ímpar
    vector<Vertex*> oddPath = oddGraph.findHamiltonianPath();
    if(oddPath.empty()) cout << "test3" <<endl;
    else{
        cout << "test5" <<endl;
        for(auto v : oddPath){
            cout << v->getId() << endl;
        }
    }
    cout << "test" <<endl;
    // 6. Combina os caminhos da MST e do subgrafo com vértices de grau ímpar
    vector<Vertex*> finalPath;
    for (auto v : mstPath) {
        cout << v->getId() << "test1" <<endl;
        finalPath.push_back(v);
    }
    for (auto v : oddPath) {
        cout << v->getId() << "teste2" <<endl;
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



