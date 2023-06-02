#ifndef DA_PROJECT2_MENU_H
#define DA_PROJECT2_MENU_H

#include "information_management/ReadData.h"
#include "graph/Algorithms.h"
#include <string>
#include <sstream>

/**
 * @brief Class representing the main menu of the project.
 */
class Menu {
public:
    /**
     * @brief Default constructor for Menu.
     */
    Menu();

    /**
     * @brief Display the main menu.
     */
    void display();

    /**
     * @brief Choose the type of graphs to use.
     */
    void chooseGraphs();

    /**
     * @brief Set the filename for the normal-sized graph.
     * @param filename The filename of the graph file.
     */
    void setGraphNormalFile(const string& filename);

    /**
     * @brief Set the filename for the large-sized graph.
     * @param filename The filename of the graph file.
     */
    void setGraphLargeFile(const string& filename);

private:
    Graph graph; /**< The graph used in the menu. */
    ReadData data; /**< The data object used for reading graph files. */
    Algorithms algorithms; /**< The algorithms object used for running algorithms on the graph. */
    bool realGraph = false;


    /**
     * @brief Display the menu for toy graphs.
     */
    void toyGraphs();

    /**
     * @brief Display the menu for medium-sized graphs.
     */
    void mediumGraphs();

    /**
     * @brief Display the menu for real-world graphs.
     */
    void realWorldGraphs();

    /**
     * @brief Display the menu for the backtracking algorithm.
     */
    void backtracking_menu();

    /**
     * @brief Display the menu for other heuristics algorithms.
     */
    void otherHeuristicsMenu();

};

#endif
