#ifndef DA_PROJECT2_GRAPH_H
#define DA_PROJECT2_GRAPH_H


#include "VertexEdge.h"

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
    [[nodiscard]] Vertex *findVertex(const int &id) const;

    /**
     * @brief Find the index of a vertex by its identifier.
     * @param id The identifier of the vertex.
     * @return The index of the found vertex or UINT_MAX if it doesn't exist.
     */
    [[nodiscard]] unsigned int findVertexIdx(const int &id) const;

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
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Get the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    [[nodiscard]] int getNumVertex() const;

    /**
     * @brief Get the set of vertices in the graph.
     * @return A vector containing the pointers to the vertices in the graph.
     */
    [[nodiscard]] std::vector<Vertex *> getVertexSet () const;

    /**
     * @brief Perform Dijkstra's algorithm to find the shortest path between two vertices.
     * @param src The identifier of the source vertex.
     * @param dest The identifier of the destination vertex.
     * @return The cost of the shortest path between the vertices, or INFINITY if there is no path.
     */
    double dijkstra(int src, int dest);

    /**
     * @brief Check if the graph is connected.
     * @return True if the graph is connected, False otherwise.
     */
    bool isConnected() const;

    /**
     * @brief Find an Eulerian path in the graph.
     * @return A vector containing the pointers to the vertices in the Eulerian path.
     */
    vector<Vertex*> findEulerianPath();

    /**
     * @brief Perform a depth-first search (DFS) to find an Eulerian path.
     * @param v The pointer to the current vertex.
     * @param edges A vector of pointers to the edges traversed in the Eulerian path.
     * @param path A vector of pointers to the vertices traversed in the Eulerian path.
     */
    void dfsEulerian(Vertex* v, vector<Vertex*>& path);

    /**
     * @brief Find a Hamiltonian path in the graph.
     * @return A vector containing the pointers to the vertices in the Hamiltonian path.
     */
    vector<Vertex*> findHamiltonianPath();

    /**
     * @brief Perform a depth-first search (DFS) to find a Hamiltonian path.
     * @param v The pointer to the current vertex.
     * @param visited A vector that marks the visited vertices.
     * @param path A vector of pointers to the vertices traversed in the Hamiltonian path.
     * @return True if a Hamiltonian path is found, False otherwise.
     */
    bool dfsHamiltonian(Vertex* v, vector<bool> &visited, vector<Vertex*> &path);

    void dfs(Vertex *v, vector<bool> &visited, vector<int> &path) const;


private:
    std::vector<Vertex *> vertexSet; /**< The set of vertices in the graph */

    /**
     * @brief Auxiliary class to compare pairs (distance, index) for the priority queue in Dijkstra's algorithm.
     */
    class Comp {
    public:
        /**
         * @brief Overloaded comparison operator for the Comp class.
         * @param p1 The first pair to be compared.
         * @param p2 The second pair to be compared.
         * @return True if p1 is less than p2, False otherwise.
         */
        bool operator()(std::pair<double, int> p1, std::pair<double, int> p2) {
            return p1.first > p2.first;
        }
    };

};

#endif
