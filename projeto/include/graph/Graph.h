//
// Created by NASA on 21/05/2023.
//

#ifndef DA_PROJECT2_GRAPH_H
#define DA_PROJECT2_GRAPH_H


#include "VertexEdge.h"

class Graph {
public:
    [[nodiscard]] Vertex *findVertex(const int &id) const;
    [[nodiscard]] unsigned int findVertexIdx(const int &id) const;
    void addVertex(Vertex* vertex);
    void addVertex(int id);
    bool removeVertex(int id);
    void addEdge(const int &source, const int &dest, double w) const;
    void addBidirectionalEdge(const int &source, const int &dest, double w) const;
    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] int getNumVertex() const;
    [[nodiscard]] std::vector<Vertex *> getVertexSet () const;

    double dijkstra(int src, int dest);

private:
    std::vector<Vertex *> vertexSet;
    class Comp {
    public:
        bool operator()(std::pair<double, int> p1, std::pair<double, int> p2) {
            return p1.first > p2.first;
        }
    };

};


#endif //DA_PROJECT2_GRAPH_H
