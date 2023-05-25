//
// Created by NASA on 21/05/2023.
//

#ifndef DA_PROJECT2_GRAPH_H
#define DA_PROJECT2_GRAPH_H


#include "VertexEdge.h"

class Graph {
public:
    Vertex *findVertex(const int &id) const;
    void addVertex(Vertex vertex);
    void addVertex(int id);
    void addEdge(const int &source, const int &dest, double w);
    void addBidirectionalEdge(const int &source, const int &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet () const;

    double dijkstra(int src, int dest);

protected:
    std::vector<Vertex *> vertexSet;

    int findVertexIdx(const int &id) const;
};


#endif //DA_PROJECT2_GRAPH_H
