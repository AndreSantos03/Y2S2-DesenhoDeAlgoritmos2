//
// Created by diogo on 29/05/2023.
//

#include "../include/Menu.h"
#include <iostream>
#include <limits>

using namespace std;


Menu::Menu() : algorithms(graph) {
    data = ReadData();
    algorithms = Algorithms(graph);
}

void Menu::setGraphNormalFile(const string &filename) {
    graph = ReadData::readNormalGraph(filename);
    algorithms.setGraph(graph);
}

void Menu::setGraphLargeFile(const string &filename) {
    graph = ReadData::readLargeGraph(filename);
    algorithms.setGraph(graph);
}

void Menu::display() {
    int choice;
    do {
        cout << "=============== MENU ===============" << endl;
        cout << "1. Load/Change Graph" << endl;
        cout << "2. Less Path" << endl;
        cout << "3. --------" << endl;
        cout << "4. Other Heuristics" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                chooseGraphs();
                break;
            case 2:
                if(!graph.isEmpty()) {
                    backtracking_menu();
                } else {
                    cout << endl;
                    cout << "The graph is empty. Please load a graph first." << endl;
                }
                break;
            case 3:
                if(!graph.isEmpty()) {
                    loadDataSet();
                } else {
                    cout << endl;
                    cout << "The graph is empty. Please load a graph first." << endl;
                }
                break;
            case 4:
                if(!graph.isEmpty()) {
                    otherHeuristicsMenu();
                } else {
                    cout << endl;
                    cout << "The graph is empty. Please load a graph first." << endl;
                }
                break;
            case 5:
                cout << "Closing the program..." << endl;
                break;
            default:
                cout << endl <<"Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 5);
}

void Menu::chooseGraphs() {
    int choice;
    do {
        cout << endl;
        cout << "=============== GRAPH SELECTOR ===============" << endl;
        cout << "1. Toy Graphs" << endl;
        cout << "2. Medium Graphs" << endl;
        cout << "3. Real World Graphs" << endl;
        cout << "4. Return" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                toyGraphs();
                return;
            case 2:
                mediumGraphs();
                return;
            case 3:
                realWorldGraphs();
                return;
            case 4:
                cout << "Returning..." << endl;
                break;
            default:
                cout << endl <<"Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 4);
}

void Menu::loadDataSet() {
    vector<Vertex*> vertices = graph.getVertexSet();
    if (vertices.empty()) {
        cout << "O conjunto de vértices está vazio." << endl;
    } else {
        cout << "Lista de arestas:" << endl;
        for (Vertex* vertex : vertices) {
            for (Edge* edge : vertex->getAdj()) {
                cout << "Origem: " << vertex->getId() << " Destino: " << edge->getDest()->getId() << endl;
                cout << endl;
            }
        }
    }
}

void Menu::toyGraphs() {
    int choice;
    do {
        cout << endl;
        cout << "=============== TOY GRAPH SELECTOR ===============" << endl;
        cout << "1. Shipping Graph" << endl;
        cout << "2. Stadiums Graph" << endl;
        cout << "3. Tourism Graph" << endl;
        cout << "4. Return" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                setGraphNormalFile("../projeto/data/toy_graphs/shipping.csv");
                return;
            case 2:
                setGraphNormalFile("../projeto/data/toy_graphs/stadiums.csv");
                return;
            case 3:
                setGraphNormalFile("../projeto/data/toy_graphs/tourism.csv");
                return;
            case 4:
                cout << "Returning..." << endl;
                break;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 4);
}

void Menu::mediumGraphs() {
    int choice;

    do {
        cout << endl;
        cout << "=============== MEDIUM GRAPH SELECTOR ===============" << endl;
        cout << "1. 25 vertices" << endl;
        cout << "2. 50 vertices" << endl;
        cout << "3. 75 vertices" << endl;
        cout << "4. 100 vertices" << endl;
        cout << "5. 200 vertices" << endl;
        cout << "6. 300 vertices" << endl;
        cout << "7. 400 vertices" << endl;
        cout << "8. 500 vertices" << endl;
        cout << "9. 600 vertices" << endl;
        cout << "10. 700 vertices" << endl;
        cout << "11. 800 vertices" << endl;
        cout << "12. 900 vertices" << endl;
        cout << "13. Return" << endl;
        cout << "Enter the number corresponding to the desired size: ";
        cin >> choice;

        switch (choice) {
            case 1:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_25.csv");
                return;
            case 2:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_50.csv");
                return;
            case 3:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_75.csv");
                return;
            case 4:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_100.csv");
                return;
            case 5:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_200.csv");
                return;
            case 6:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_300.csv");
                return;
            case 7:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_400.csv");
                return;
            case 8:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_500.csv");
                return;
            case 9:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_600.csv");
                return;
            case 10:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_700.csv");
                return;
            case 11:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_800.csv");
                return;
            case 12:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_900.csv");
                return;
            case 13:
                cout << "Returning..." << endl;
                break;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 13);
}

void Menu::realWorldGraphs() {
    int choice;

    do {
        cout << endl;
        cout << "=============== REAL WORLD GRAPH SELECTOR ===============" << endl;
        cout << "1. Graph 1" << endl;
        cout << "2. Graph 2" << endl;
        cout << "3. Graph 3" << endl;
        cout << "4. Return" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                setGraphLargeFile("../projeto/data/real_world_graphs/graph1");
                return;
            case 2:
                setGraphLargeFile("../projeto/data/real_world_graphs/graph2");
                return;
            case 3:
                setGraphLargeFile("../projeto/data/real_world_graphs/graph3");
                return;
            case 4:
                cout << "Returning..." << endl;
                break;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 4);
}


void Menu::backtracking_menu(){
    std::vector<int> path = {0}; // Vetor para armazenar o caminho atual
    std::vector<bool> visited(graph.getNumVertex(), false); // Vetor para controlar os vértices visitados
    double min_cost = std::numeric_limits<double>::max();
    visited[0] = true;
    algorithms.backtracking(path, visited, min_cost, 0.0);
    cout << min_cost << endl;
}

void Menu::otherHeuristicsMenu() {
    string choice;
    while(true){
        cout << "=============== Other Heuristics ===============" << endl;
        cout << "1. Cluster Based Algorithm" << endl;
        cout << "4. Return" << endl;
        cin >> choice;
        if(choice == "1"){
            while(true){
                cout << "Choose number of clusters: ";
                int clusterNum = cin_int();
                vector<Vertex*> path = algorithms.clusterBasedAlgorithm(clusterNum);
                for(auto v:path){
                    cout << v->getId() << endl;
                }
                break;
            }
        }
    }

}

int Menu::cin_int()
{
    int choice = 0;
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

