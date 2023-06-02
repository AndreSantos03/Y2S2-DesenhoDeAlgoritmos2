#ifndef DA_PROJECT2_ALGORITHMS_H
#define DA_PROJECT2_ALGORITHMS_H

#include "Graph.h"
#include "VertexEdge.h"
#include "MutablePriorityQueue.h"
#include <cmath>
#include <algorithm>
#include <vector>

/**
 * @brief Class that contains various graph algorithms.
 */
class Algorithms {
public:
    /**
     * @brief Default constructor for Algorithms.
     */
    Algorithms();

    /**
     * @brief Constructor for Algorithms that sets the graph.
     * @param graph The graph to be used by the algorithms.
     */
    explicit Algorithms(Graph graph);

    /**
     * @brief Set the graph to be used by the algorithms.
     * @param graph_ The graph to be set.
     */
    void setGraph(Graph graph_);

    /**
     * @brief Set all vertices in the graph as non-visited.
     */
    void setAllNonVisited();

    /**
     * @brief Backtracking algorithm to find the minimum weight Hamiltonian cycle.
     * @param curr_vertex The current vertex being visited.
     * @param visited A vector indicating which vertices have been visited.
     * @param count The number of vertices visited so far.
     * @param weight The weight of the current path.
     * @param min_weight The minimum weight found so far.
     * @param start_vertex The starting vertex of the cycle.
     * @param min_path The minimum weight Hamiltonian cycle found.
     * @param curr_path The current path being explored.
     * @return The minimum weight of the Hamiltonian cycle.
     */
    double backtracking(Vertex* curr_vertex, std::vector<bool>& visited, int count, double weight, double min_weight, Vertex* start_vertex, std::vector<int>& min_path, std::vector<int>& curr_path);

    /**
     * @brief Prim's algorithm to find the minimum spanning tree of the graph.
     * @return The weight of the minimum spanning tree.
     */
    double primMST();

    /**
     * @brief Prim's algorithm to find the minimum spanning tree of the graph.
     * @return The minimum spanning tree as a graph.
     */
    Graph primMSTgraph();

    /**
     * @brief Cluster-based algorithm to divide the graph into a specified number of clusters.
     * @param numClusters The number of clusters to create.
     * @return A vector of vertices representing the clusters.
     */
    std::vector<Vertex*> clusterBasedAlgorithm(int numClusters);

    /**
     * @brief Christofides algorithm to find an approximate solution to the Traveling Salesman Problem (TSP).
     * @return A vector of vertices representing the approximate TSP path.
     */
    std::vector<Vertex*> christofidesTSP();

private:
    /**
     * @brief Calculate the cost of a given path.
     * @param path The path for which to calculate the cost.
     * @return The cost of the path.
     */
    double calculatePathCost(std::vector<Vertex*> path);

    /**
     * @brief Calculate the Euclidean distance between two vertices.
     * @param source The source vertex.
     * @param dest The destination vertex.
     * @return The Euclidean distance between the vertices.
     */
    static double calculateDistance(Vertex* source, Vertex* dest);

    Graph graph;    /**< The graph used by the algotirhms. */
};

#endif
