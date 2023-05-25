//
// Created by NASA on 21/05/2023.
//

#include "../../include/graph/Graph.h"
#include <xmath.h>
#include <queue>
#include <vector>

Vertex *Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

void Graph::addVertex(Vertex vertex) {
    vertexSet.push_back(&vertex);
}

void Graph::addVertex(int id){
    Vertex v(id);
     vertexSet.push_back(&v);
}

void Graph::addEdge(const int &source, const int &dest, double w) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    v1->addEdge(v2, w);
}

void Graph::addBidirectionalEdge(const int &source, const int &dest, double w) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

class comp{
public:
    bool operator()(std::pair<double,int> p1, std::pair<double,int> p2){
        return p1.first < p2.first;
    }
};

double Graph::dijkstra(int src, int dest) {

    for  (auto& i : vertexSet) {
        i->setVisited(false);
        i->setDist(INF);
    }

    std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int>>,comp> q;

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



