//
// Created by NASA on 21/05/2023.
//

#ifndef DA_PROJECT2_VERTEXEDGE_H
#define DA_PROJECT2_VERTEXEDGE_H

#include <iostream>
#include <vector>

using namespace std;

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    Vertex(int id, string label);
    Vertex(int id, int longitude, int latitude);
    bool operator<(Vertex & vertex) const;

    bool getVisited();
    int getId() const;
    double getDist();
    std::vector<Edge *> getAdj() const;


    void setVisited(bool info);
    void setId(int info);
    void setDist(double dist);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();
    std::vector<Edge *> getIncoming() const;

    string getLabel();

protected:
    int id;
    string label;
    int longitude;
    int latitude;
    std::vector<Edge *> adj;
    double dist;
    bool visited;

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
    Edge *getReverse() const;

    void setReverse(Edge *reverse);


private:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    Vertex *orig;
    Edge *reverse;
};


#endif //DA_PROJECT2_VERTEXEDGE_H
