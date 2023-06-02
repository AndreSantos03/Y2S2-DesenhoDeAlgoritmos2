#ifndef VERTEXEDGE_H
#define VERTEXEDGE_H

#include <iostream>
#include <vector>

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    explicit Vertex(int id);
    Vertex(int id, std::string label);
    Vertex(int id, double longitude, double latitude);

    bool operator<(const Vertex& vertex) const;

    [[nodiscard]] int getId() const;
    [[nodiscard]] double getDist() const;
    [[nodiscard]] std::vector<Edge*> getAdj() const;
    [[nodiscard]] std::vector<Edge*> getIncoming() const;
    [[nodiscard]] bool getVisited() const;
    [[nodiscard]] double getLongitude() const;
    [[nodiscard]] double getLatitude() const;
    [[nodiscard]] std::string getLabel() const;
    [[nodiscard]] bool isVisited() const;
    Edge* getEdge(Vertex* dest);

    void setId(int info);
    void setDist(double dist_);
    void setVisited(bool info);

    Edge* addEdge(Vertex* dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();

protected:
    int id;
    std::string label;
    double longitude{};
    double latitude{};
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    double dist{};
    bool visited;

    void deleteEdge(Edge* edge) const;
};

/********************** Edge ****************************/

class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, double w);

    [[nodiscard]] Vertex* getDest() const;
    [[nodiscard]] Vertex* getOrig() const;
    [[nodiscard]] double getWeight() const;
    [[nodiscard]] Edge* getReverse() const;

    void setReverse(Edge* reverse_);

private:
    Vertex* orig;
    Vertex* dest;
    double weight;
    Edge* reverse;
};

#endif // VERTEXEDGE_H
