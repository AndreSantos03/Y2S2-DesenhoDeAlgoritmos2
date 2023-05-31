//
// Created by NASA on 21/05/2023.
//

#include <utility>

#include "../../include/graph/VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id) : id(id), visited(false) {}

Vertex::Vertex(int id, std::string label) : id(id), label(std::move(label)), visited(false) {}

Vertex::Vertex(int id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude), visited(false) {}

bool Vertex::operator<(const Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

double Vertex::getDist() const {
    return this->dist;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

bool Vertex::getVisited() const {
    return visited;
}

double Vertex::getLongitude() const {
    return longitude;
}

double Vertex::getLatitude() const {
    return latitude;
}

std::string Vertex::getLabel() const {
    return label;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setId(int info) {
    this->id = info;
}

void Vertex::setDist(double dist_) {
    this->dist = dist_;
}

void Vertex::setVisited(bool info) {
    visited = info;
}

Edge *Vertex::addEdge(Vertex *dest, double w) {
    Edge *newEdge = new Edge(this, dest, w);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        } else {
            it++;
        }
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

void Vertex::deleteEdge(Edge *edge) const {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        } else {
            it++;
        }
    }
    delete edge;
}

Edge *Vertex::getEdge(Vertex *dest) {
    for(auto e : adj){
        if(e->getDest() == dest){
            return e;
        }
    }
    return nullptr;
}

/************************* Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w) : orig(orig), dest(dest), weight(w), reverse(nullptr) {}

Vertex *Edge::getDest() const {
    return dest;
}

Vertex *Edge::getOrig() const {
    return orig;
}

double Edge::getWeight() const {
    return weight;
}

Edge *Edge::getReverse() const {
    return reverse;
}

void Edge::setReverse(Edge *reverse_) {
    this->reverse = reverse_;
}
