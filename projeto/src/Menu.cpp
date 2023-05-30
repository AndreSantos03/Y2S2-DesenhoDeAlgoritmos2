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
    graph = data.readNormalGraph(filename);
}

void Menu::setGraphLargeFile(const string &filename) {
    graph = data.readLargeGraph(filename);
}

void Menu::display() {
    int choice;
    std::vector<int> path; // Vetor para armazenar o caminho atual
    std::vector<bool> visited(graph.getNumVertex(), false); // Vetor para controlar os vértices visitados
    double min_cost = std::numeric_limits<double>::max();
    do {
        cout << "=============== MENU ===============" << endl;
        cout << "1. Select Graph" << endl;
        cout << "2. Less Path" << endl;
        cout << "3. --------" << endl;
        cout << "4. --------" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                chooseGraphs();
                break;
            case 2:
                path.push_back(0); // Adicionar o vértice inicial ao caminho
                visited[0] = true; // Marcar o vértice inicial como visitado
                algorithms.backtracking(path, visited, min_cost, 0.0);
                cout << min_cost << endl;
                break;
            case 3:
                loadDataSet();
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
        cout << "CHOOSE THE GRAPHS:" << endl;
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
                return;
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
        cout << "CHOOSE THE GRAPH:" << endl;
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
                return;
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
        cout << "CHOOSE THE GRAPH (25/50/75/100/200/300/400/500/600/700/800/900 or 1 to return):";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Returning..." << endl;
                return;
            case 25:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_25.csv");
                return;
            case 50:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_50.csv");
                return;
            case 75:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_75.csv");
                return;
            case 100:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_100.csv");
                return;
            case 200:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_200.csv");
                return;
            case 300:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_300.csv");
                return;
            case 400:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_400.csv");
                return;
            case 500:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_500.csv");
                return;
            case 600:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_600.csv");
                return;
            case 700:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_700.csv");
                return;
            case 800:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_800.csv");
                return;
            case 900:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_900.csv");
                return;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 1);
}

void Menu::realWorldGraphs() {
    int choice;
    do {
        cout << endl;
        cout << "CHOOSE THE GRAPH DIRECTORY(1/2/3 or 4 to return):" << endl;
        cout << "Choose an option:";
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
                return;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 4);
}


