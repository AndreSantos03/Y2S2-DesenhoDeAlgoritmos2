#include "../../include/graph/Graph.h"
#include <xmath.h>
#include <queue>
#include <vector>



Vertex* Graph::findVertex(const int& id) const {
    for (auto v : vertexSet) {
        if (v->getId() == id) {

            return v;
        }
    }
    return nullptr;
}
unsigned int Graph::findVertexIdx(const int& id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++) {
        if (vertexSet[i]->getId() == id) {
            return i;
        }
    }
    return -1;
}

void Graph::addVertex(Vertex* vertex) {
    vertexSet.push_back(vertex);
}

bool Graph::removeVertex(int id) {
    Vertex* vertexToRmv = findVertex(id);
    if (vertexToRmv == nullptr) {
        return false;
    }

    for (auto edge : vertexToRmv->getAdj()) {
        auto temp = edge->getDest();
        temp->removeEdge(vertexToRmv->getId());
        vertexToRmv->removeEdge(temp->getId());
    }

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getId() == id){
            vertexSet.erase(it);
            break;
        }
    }

    delete vertexToRmv;
    return true;
}

void Graph::addVertex(int id){
    auto* v = new Vertex(id);
    vertexSet.push_back(v);
}

void Graph::addEdge(const int &source, const int &dest, double w) const {
    Vertex* v1 = findVertex(source);
    Vertex* v2 = findVertex(dest);
    if (v1 && v2) {
        v1->addEdge(v2, w);
    }
}

void Graph::addBidirectionalEdge(const int &source, const int &dest, double w) const {
    Vertex* v1 = findVertex(source);
    Vertex* v2 = findVertex(dest);
    if (v1 && v2) {
        Edge* e1 = v1->addEdge(v2, w);
        Edge* e2 = v2->addEdge(v1, w);
        e1->setReverse(e2);
        e2->setReverse(e1);
    }
}

bool Graph::isConnected() const {
    if (vertexSet.empty()) {
        return false;  // Grafo vazio não é considerado conexo
    }

    int numVertices = getNumVertex();
    vector<bool> visited(numVertices, false);

    // Realiza uma busca em largura a partir de um vértice inicial
    int startVertex = vertexSet.front()->getId();
    queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        int currVertex = q.front();
        q.pop();

        for (auto edge : vertexSet[currVertex]->getAdj()) {
            int neighbor = edge->getDest()->getId();
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    // Verifica se todos os vértices foram visitados
    for (bool v : visited) {
        if (!v) {
            return false;  // Grafo não é conexo
        }
    }

    return true;  // Grafo é conexo
}


int Graph::getNumVertex() const {
    return (int) vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}



double Graph::dijkstra(int src, int dest) {

    for  (auto& i : vertexSet) {
        i->setVisited(false);
        i->setDist(INF);
    }

    std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int>>,Comp> q;

    q.emplace(0,src);

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if(curr.second == dest) return curr.first;
        findVertex(curr.second)->setVisited(true);
        findVertex(curr.second)->setDist(curr.first);

        for(auto e: findVertex(curr.second)->getAdj()){
            if(e->getDest()->getId() != curr.second && !e->getDest()->getVisited()){
                q.emplace(curr.first+e->getWeight(),e->getDest()->getId());
            }
        }
    }
    return -1;
}

void Graph::dfs(Vertex* v, std::vector<bool>& visited) const {
    visited[findVertexIdx(v->getId())] = true;

    for (auto edge : v->getAdj()) {
        Vertex* dest = edge->getDest();
        if (!visited[findVertexIdx(dest->getId())]) {
            dfs(dest, visited);
        }
    }
}

bool Graph::isEmpty() const {
    return vertexSet.empty();
}

vector<Vertex*> Graph::findEulerianPath() {
    vector<Vertex*> path;

    // Verifica se o grafo é conexo
    if (!isConnected()) {
        return path;
    }

    // Encontra um vértice inicial com grau ímpar
    Vertex* startVertex = nullptr;
    for (auto v : vertexSet) {
        if (v->getAdj().size() % 2 != 0) {
            startVertex = v;
            break;
        }
    }

    // Se não encontrou um vértice com grau ímpar, seleciona um vértice qualquer
    if (startVertex == nullptr) {
        startVertex = vertexSet.front();
    }

    // Realiza o percurso Euleriano
    dfsEulerian(startVertex, path);

    return path;
}

void Graph::dfsEulerian(Vertex* v, vector<Vertex*>& path) {
    while (!v->getAdj().empty()) {
        Edge* e = v->getAdj().front();
        Vertex* dest = e->getDest();

        v->removeEdge(dest->getId());
        dest->removeEdge(v->getId());

        dfsEulerian(dest, path);
    }

    path.push_back(v);
}

vector<Vertex*> Graph::findHamiltonianPath() {
    vector<Vertex*> path;
    vector<bool> visited(getNumVertex(), false);

    // Realiza o percurso Hamiltoniano a partir de cada vértice
    for (auto v : vertexSet) {
        path.push_back(v);
        if (dfsHamiltonian(v, visited, path)) {
            return path;
        }
        path.clear();
        visited.assign(getNumVertex(), false);
    }

    return path;
}

bool Graph::dfsHamiltonian(Vertex* v, vector<bool>& visited, vector<Vertex*>& path) {
    if (path.size() == vertexSet.size()) {
        return true;  // Encontrou um caminho Hamiltoniano completo
    }

    visited[findVertexIdx(v->getId())] = true;

    for (auto e : v->getAdj()) {
        Vertex* dest = e->getDest();
        if (!visited[findVertexIdx(dest->getId())]) {
            path.push_back(dest);

            if (dfsHamiltonian(dest, visited, path)) {
                return true;
            }

            path.pop_back();
        }
    }

    visited[findVertexIdx(v->getId())] = false;

    return false;  // Não encontrou um caminho Hamiltoniano completo
}

