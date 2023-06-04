#ifndef DA_PROJECT2_GRAPH_H
#define DA_PROJECT2_GRAPH_H

#include "VertexEdge.h"
#include <vector>

using namespace std;

/**
 * @brief Class that represents a graph.
 */
class Graph {
public:
    /**
     * @brief Find a vertex by its identifier.
     * @param id The identifier of the vertex to be found.
     * @return A pointer to the found vertex or nullptr if it doesn't exist.
     */
    Vertex *findVertex(const int &id) const;

    /**
     * @brief Find the index of a vertex by its identifier.
     * @param id The identifier of the vertex.
     * @return The index of the found vertex or UINT_MAX if it doesn't exist.
     */
    unsigned int findVertexIdx(const int &id) const;

    /**
     * @brief Add a vertex to the graph.
     * @param vertex The pointer to the vertex to be added.
     */
    void addVertex(Vertex* vertex);

    /**
     * @brief Add a vertex to the graph based on its identifier.
     * @param id The identifier of the vertex to be added.
     */
    void addVertex(int id);

    /**
     * @brief Remove a vertex from the graph based on its identifier.
     * @param id The identifier of the vertex to be removed.
     * @return True if the vertex was successfully removed, False otherwise.
     */
    bool removeVertex(int id);

    /**
     * @brief Add a directed edge to the graph.
     * @param source The identifier of the source vertex.
     * @param dest The identifier of the destination vertex.
     * @param w The weight of the edge.
     */
    void addEdge(const int &source, const int &dest, double w) const;

    /**
     * @brief Add a bidirectional edge to the graph.
     * @param source The identifier of the source vertex.
     * @param dest The identifier of the destination vertex.
     * @param w The weight of the edge.
     */
    void addBidirectionalEdge(const int &source, const int &dest, double w) const;

    /**
     * @brief Check if the graph is empty.
     * @return True if the graph is empty, False otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Get the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    int getNumVertex() const;

    /**
     * @brief Get the set of vertices in the graph.
     * @return A vector containing the pointers to the vertices in the graph.
     */
    vector<Vertex *> getVertexSet () const;

    /**
     * @brief Find an Eulerian path in the graph.
     * @return A vector containing the pointers to the vertices in the Eulerian path.
     */
    vector<Vertex*> findEulerianPath();

    /**
     * @brief Perform a depth-first search (DFS) to find an Eulerian path.
     * @param v The pointer to the current vertex.
     * @param path A vector of pointers to the vertices traversed in the Eulerian path.
     */
    void dfsEulerian(Vertex* v, vector<Vertex*>& path);

    /**
     * @brief Perform a depth-first search (DFS) to find the connected component of a vertex.
     * @param v The pointer to the current vertex.
     * @param visited A vector indicating which vertices have been visited.
     * @param path A vector of vertices representing the connected component.
     */
    void dfs(Vertex *v, vector<bool> &visited, vector<int> &path) const;

    /**
     * @brief Calculate the minimum weight matching for the vertices in the graph.
     * @return A vector containing the pointers to the edges in the minimum weight matching.
     */
    vector<Edge *> calculateMinimumMatching();

private:
    vector<Vertex *> vertexSet; /**< The set of vertices in the graph */

};

#endif
