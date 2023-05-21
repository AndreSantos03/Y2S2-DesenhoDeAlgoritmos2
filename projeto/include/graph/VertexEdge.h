//
// Created by NASA on 21/05/2023.
//

#ifndef DA_PROJECT2_VERTEXEDGE_H
#define DA_PROJECT2_VERTEXEDGE_H

#include <iostream>
#include <vector>

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    bool operator<(Vertex & vertex) const;

    int getId() const;
    std::vector<Edge *> getAdj() const;

    void setId(int info);
    void setDist(double dist);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();

protected:
    int id;
    std::vector<Edge *> adj;
    double dist;

    std::vector<Edge *> incoming;

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge{
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    Vertex * getOrig() const;
private:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    Vertex *orig;
    Edge *reverse;
};


#endif //DA_PROJECT2_VERTEXEDGE_H
