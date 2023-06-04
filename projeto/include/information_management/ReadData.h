#ifndef DA_PROJECT2_READDATA_H
#define DA_PROJECT2_READDATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <unordered_set>
#include "../graph/Graph.h"

using namespace std;

/**
 * @brief Class for reading graph data from files.
 */
class ReadData {
public:
    /**
     * @brief Default constructor for ReadData.
     */
    ReadData();

    /**
     * @brief Read a normal-sized graph from a file.
     * @param filename The name of the file to read.
     * @return The graph read from the file.
     */
    static Graph readNormalGraph(const string& filename);

    /**
     * @brief Read a large-sized graph from a file.
     * @param filename The name of the file to read.
     * @return The graph read from the file.
     */
    static Graph readLargeGraph(const string& filename);
};

#endif
