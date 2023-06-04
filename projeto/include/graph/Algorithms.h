#ifndef DA_PROJECT2_ALGORITHMS_H
#define DA_PROJECT2_ALGORITHMS_H

#include "Graph.h"
#include "VertexEdge.h"
#include "MutablePriorityQueue.h"
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

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
     * In the worst case, for a complete graph where each vertex is connected to all other vertices, the complexity of the algorithm would be O(n!).
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
    double backtracking(Vertex* curr_vertex, vector<bool>& visited, int count, double weight, double min_weight, Vertex* start_vertex, vector<int>& min_path, vector<int>& curr_path);

    /**
     * @brief Prim's algorithm to find the minimum spanning tree of the graph.
     * The overall time complexity of the primMSTgraph function is O(V log V + E log V), where V is the number of vertices and E is the number of edges in the original graph.
     * @return The minimum spanning tree as a graph.
     */
    Graph primMSTgraph();

    /**
     * @brief Cluster-based algorithm to divide the graph into a specified number of clusters.
     * The time complexity of the clusterBasedAlgorithm remains dominated by the sorting step, which is O(V log V).
     * @param numClusters The number of clusters to create.
     * @return A vector of vertices representing the clusters.
     */
    vector<Vertex*> clusterBasedAlgorithm(int numClusters);

    /**
     * @brief Christofides algorithm to find an approximate solution to the (TSP).
     * The christofidesTSP function is dominated by the complexity of calculating the MST using Prim's algorithm, resulting in a time complexity of O(V^2 log V).
     * @return A vector of vertices representing the approximate TSP path.
     */
    vector<Vertex*> christofidesTSP();

    /**
     * @brief Nearest neighbor algorithm to find an approximate solution to the (TSP).
     * The overall time complexity of the nearestNeighbor algorithm is O(V), where V is the number of vertices in the graph.
     * @return A vector of vertices representing the approximate TSP path.
     */
    vector<Vertex*> nearestNeighbor();

    /**
     * @brief Calculate the cost of a given path.
     * @param path The path for which to calculate the cost.
     * @return The cost of the path.
     */
    static double calculatePathCost(vector<Vertex*> path);

private:
    /**
     * @brief Calculate the Euclidean distance between two vertices.
     * @param source The source vertex.
     * @param dest The destination vertex.
     * @return The Euclidean distance between the vertices.
     */
    static double calculateDistance(Vertex* source, Vertex* dest);

    /**
     * @brief Find the nearest vertex to the current vertex within a cluster.
     * The overall time complexity of the findNearestVertex function is O(E + V).
     * @param current The current vertex.
     * @param cluster The cluster of vertices to search in.
     * @return The nearest vertex in the cluster to the current vertex.
     */
    Vertex *findNearestVertex(Vertex *current, vector<Vertex *> cluster);

    /**
     * @brief Find the nearest vertex to the current vertex in the graph.
     * The overall time complexity of the findNearestVertex function is O(E + V).
     * @param current The current vertex.
     * @return The nearest vertex in the graph to the current vertex.
     */
    Vertex *findNearestVertex(Vertex *current);

    Graph graph;    /**< The graph used by the algorithms. */

};

#endif
