#ifndef VERTEXEDGE_H
#define VERTEXEDGE_H

#include <iostream>
#include <vector>
#include "MutablePriorityQueue.h"

using namespace std;

class Edge;

/************************* Vertex  **************************/

/**
 * @brief Class that represents a vertex in a graph.
 */
class Vertex {
public:
    /**
     * @brief Constructs a vertex with the given identifier.
     * @param id The identifier of the vertex.
     */
    explicit Vertex(int id);

    /**
     * @brief Constructs a vertex with the given identifier and label.
     * @param id The identifier of the vertex.
     * @param label The label of the vertex.
     */
    Vertex(int id, string label);

    /**
     * @brief Constructs a vertex with the given identifier, longitude, and latitude.
     * @param id The identifier of the vertex.
     * @param longitude The longitude of the vertex.
     * @param latitude The latitude of the vertex.
     */
    Vertex(int id, double longitude, double latitude);

    /**
     * @brief Overloaded less-than operator for comparing vertices.
     * @param vertex The vertex to compare with.
     * @return True if this vertex has a lower ID than the given vertex, False otherwise.
     */
    bool operator<(const Vertex& vertex) const;

    /**
     * @brief Get the identifier of the vertex.
     * @return The identifier of the vertex.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Get the distance of the vertex (used in algorithms like Dijkstra's algorithm).
     * @return The distance of the vertex.
     */
    [[nodiscard]] double getDist() const;

    /**
     * @brief Get the outgoing edges of the vertex.
     * @return A vector containing pointers to the outgoing edges.
     */
    [[nodiscard]] vector<Edge*> getAdj() const;

    /**
     * @brief Get the incoming edges of the vertex.
     * @return A vector containing pointers to the incoming edges.
     */
    [[nodiscard]] vector<Edge*> getIncoming() const;

    /**
     * @brief Get the longitude of the vertex.
     * @return The longitude of the vertex.
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Get the latitude of the vertex.
     * @return The latitude of the vertex.
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Get the label of the vertex.
     * @return The label of the vertex.
     */
    [[nodiscard]] string getLabel() const;

    /**
     * @brief Check if the vertex has been visited.
     * @return True if the vertex has been visited, False otherwise.
     */
    [[nodiscard]] bool isVisited() const;

    /**
     * @brief Get the path edge leading to this vertex (used in algorithms like Dijkstra's algorithm).
     * @return A pointer to the path edge.
     */
    [[nodiscard]] Edge* getPath() const;

    /**
     * @brief Get the edge between this vertex and a specified destination vertex.
     * @param dest The destination vertex.
     * @return A pointer to the edge between this vertex and the destination vertex.
     */
    Edge* getEdge(Vertex* dest);

    /**
     * @brief Set the identifier of the vertex.
     * @param id The identifier of the vertex.
     */
    void setId(int id);

    /**
     * @brief Set the distance of the vertex.
     * @param dist The distance of the vertex.
     */
    void setDist(double dist);

    /**
     * @brief Set the visited status of the vertex.
     * @param visited The visited status of the vertex.
     */
    void setVisited(bool visited);

    /**
     * @brief Set the path edge leading to this vertex.
     * @param path The path edge leading to this vertex.
     */
    void setPath(Edge* path);

    /**
     * @brief Add an outgoing edge from this vertex to a specified destination vertex with the given weight.
     * @param dest The destination vertex.
     * @param w The weight of the edge.
     * @return A pointer to the added edge.
     */
    Edge* addEdge(Vertex* dest, double w);

    /**
     * @brief Remove the edge between this vertex and a specified destination vertex.
     * @param destID The identifier of the destination vertex.
     * @return True if the edge was successfully removed, False otherwise.
     */
    bool removeEdge(int destID);

    /**
     * @brief Delete an edge from the vertex's adjacency list.
     * @param edge The edge to be deleted.
     */
    void deleteEdge(Edge* edge) const;

    /**
     * @brief Remove all outgoing edges from this vertex.
     */
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

protected:
    int id;                         /**< Vertex identifier */
    string label;              /**< Vertex label */
    double longitude;               /**< Vertex longitude */
    double latitude;                /**< Vertex latitude */
    vector<Edge*> adj;         /**< Outgoing edges */
    vector<Edge*> incoming;    /**< Incoming edges */
    double dist;                    /**< Distance (used in algorithms like Dijkstra's algorithm) */
    bool visited = false;           /**< Visited flag */
    Edge* path = nullptr;           /**< Path edge (used in algorithms like Dijkstra's algorithm) */

    int queueIndex = 0;             /**< Required by MutablePriorityQueue and UFDS */
};

/********************** Edge ****************************/

/**
 * @brief Class that represents an edge in a graph.
 */
class Edge {
public:
    /**
     * @brief Constructs an edge between two vertices with the given weight.
     * @param orig The origin vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @param w The weight of the edge.
     */
    Edge(Vertex* orig, Vertex* dest, double w);

    /**
     * @brief Get the destination vertex of the edge.
     * @return A pointer to the destination vertex.
     */
    [[nodiscard]] Vertex* getDest() const;

    /**
     * @brief Get the origin vertex of the edge.
     * @return A pointer to the origin vertex.
     */
    [[nodiscard]] Vertex* getOrig() const;

    /**
     * @brief Get the weight of the edge.
     * @return The weight of the edge.
     */
    [[nodiscard]] double getWeight() const;

    /**
     * @brief Get the reverse edge.
     * @return A pointer to the reverse edge.
     */
    [[nodiscard]] Edge* getReverse() const;

    /**
     * @brief Set the reverse edge of this edge.
     * @param reverse_ The reverse edge.
     */
    void setReverse(Edge* reverse_);

private:
    Vertex* orig;       /**< Origin vertex */
    Vertex* dest;       /**< Destination vertex */
    double weight;      /**< Edge weight */
    Edge* reverse;      /**< Reverse edge */
};

#endif
