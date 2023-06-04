#include "../../include/graph/Graph.h"
#include <xmath.h>
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>


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
            if(e->getDest()->getId() != curr.second && !e->getDest()->isVisited()){
                q.emplace(curr.first+e->getWeight(),e->getDest()->getId());
            }
        }
    }
    return -1;
}

void Graph::dfs(Vertex* v, vector<bool>& visited, vector<int>& path) const {
    visited[findVertexIdx(v->getId())] = true;
    path.push_back(v->getId());

    for (auto edge : v->getAdj()) {
        Vertex* dest = edge->getDest();
        if (!visited[findVertexIdx(dest->getId())]) {
            dfs(dest, visited, path);
        }
    }
}

bool Graph::isEmpty() const {
    return vertexSet.empty();
}

// Função para calcular o emparelhamento perfeito mínimo usando o algoritmo de Edmonds
vector<Edge*> Graph::calculateMinimumMatching() {
    vector<Edge*> matching;
    unordered_set<int> matchedVertices;

    for (auto vertex : getVertexSet()) {
        if (matchedVertices.count(vertex->getId()) == 0) {
            Edge* minWeightEdge = nullptr;

            for (auto edge : vertex->getAdj()) {
                if (matchedVertices.count(edge->getDest()->getId()) == 0) {
                    if (minWeightEdge == nullptr || edge->getWeight() < minWeightEdge->getWeight()) {
                        minWeightEdge = edge;
                    }
                }
            }

            if (minWeightEdge != nullptr) {
                matching.push_back(minWeightEdge);
                matchedVertices.insert(vertex->getId());
                matchedVertices.insert(minWeightEdge->getDest()->getId());
            }
        }
    }

    return matching;
}


vector<Vertex*> Graph::findEulerianPath() {
    vector<Vertex*> eulerianPath;

    if (vertexSet.empty()) {
        return eulerianPath;
    }

    stack<pair<Vertex*, Edge*>> path;
    Vertex* startVertex = vertexSet[0];
    path.push({startVertex, nullptr});

    while (!path.empty()) {
        Vertex* currentVertex = path.top().first;
        Edge* prevEdge = path.top().second;

        if (!currentVertex->getAdj().empty()) {
            Edge* nextEdge = nullptr;

            for (auto edge : currentVertex->getAdj()) {
                if (edge != prevEdge) {
                    nextEdge = edge;
                    break;
                }
            }

            if (nextEdge != nullptr) {
                Vertex* nextVertex = nextEdge->getDest();

                // Remove a aresta da lista de adjacências
                currentVertex->removeEdge(nextVertex->getId());

                path.push({nextVertex, nextEdge});
            }
            else {
                eulerianPath.push_back(currentVertex);
                path.pop();
            }
        }
        else {
            eulerianPath.push_back(currentVertex);
            path.pop();
        }
    }

    eulerianPath.insert(eulerianPath.begin(), startVertex);
    return eulerianPath;
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

