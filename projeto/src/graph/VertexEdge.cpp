//
// Created by NASA on 21/05/2023.
//

#include "../../include/graph/VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id): id(id) {}

Vertex::Vertex(int id, string label): id(id), label(label){};

Vertex::Vertex(int id, int longitude, int latitude): id(id), longitude(longitude), latitude(latitude){};

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

void Vertex::setId(int info) {
    this->id = id;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

Edge *Vertex::addEdge(Vertex *dest, double w) {
    auto newEdge = new Edge(this, dest, w);
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
        }
        else {
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

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

string Vertex::getLabel() {
    return label;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w):orig(orig), dest(dest), weight(w) {}

Vertex *Edge::getDest() const {
    this->dest;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

double Edge::getWeight() const {
    return weight;
}

Edge *Edge::getReverse() const {
    return reverse;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}


