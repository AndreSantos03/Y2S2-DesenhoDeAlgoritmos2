//
// Created by NASA on 21/05/2023.
//

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
int Graph::findVertexIdx(const int& id) const {
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
    Vertex* v = new Vertex(id);
    vertexSet.push_back(v);
}

void Graph::addEdge(const int &source, const int &dest, double w) {
    Vertex* v1 = findVertex(source);
    Vertex* v2 = findVertex(dest);
    if (v1 && v2) {
        v1->addEdge(v2, w);
    }
}

void Graph::addBidirectionalEdge(const int &source, const int &dest, double w) {
    Vertex* v1 = findVertex(source);
    Vertex* v2 = findVertex(dest);
    if (v1 && v2) {
        Edge* e1 = v1->addEdge(v2, w);
        Edge* e2 = v2->addEdge(v1, w);
        e1->setReverse(e2);
        e2->setReverse(e1);
    }
}


int Graph::getNumVertex() const {
    return vertexSet.size();
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

    q.push({0,src});

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if(curr.second == dest) return curr.first;
        findVertex(curr.second)->setVisited(true);
        findVertex(curr.second)->setDist(curr.first);

        for(auto e: findVertex(curr.second)->getAdj()){
            if(e->getDest()->getId() != curr.second && !e->getDest()->getVisited()){
                q.push({curr.first+e->getWeight(),e->getDest()->getId()});
            }
        }
    }
    return -1;
}



