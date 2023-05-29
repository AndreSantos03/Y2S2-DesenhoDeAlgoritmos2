#ifndef VERTEXEDGE_H
#define VERTEXEDGE_H

#include <iostream>
#include <vector>

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    Vertex(int id, std::string label);
    Vertex(int id, int longitude, int latitude);

    bool operator<(const Vertex& vertex) const;

    int getId() const;
    double getDist() const;
    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;
    bool getVisited() const;
    int getLongitude() const;
    int getLatitude() const;
    std::string getLabel() const;
    bool isVisited() const;

    void setId(int info);
    void setDist(double dist);
    void setVisited(bool info);

    Edge* addEdge(Vertex* dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();

protected:
    int id;
    std::string label;
    int longitude;
    int latitude;
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    double dist;
    bool visited;

    void deleteEdge(Edge* edge);
};

/********************** Edge ****************************/

class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, double w);

    Vertex* getDest() const;
    Vertex* getOrig() const;
    double getWeight() const;
    Edge* getReverse() const;

    void setReverse(Edge* reverse);

private:
    Vertex* orig;
    Vertex* dest;
    double weight;
    Edge* reverse;
};

#endif // VERTEXEDGE_H
