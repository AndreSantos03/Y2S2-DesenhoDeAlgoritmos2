//
// Created by diogo on 29/05/2023.
//

#include "../include/Menu.h"
#include <iostream>

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
    do {
        cout << "=============== MENU ===============" << endl;
        cout << "CHOOSE THE GRAPHS:" << endl;
        cout << "1. Toy Graphs" << endl;
        cout << "2. Medium Graphs" << endl;
        cout << "3. Real World Graphs" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                toyGraphs();
                break;
            case 2:
                mediumGraphs();
                break;
            case 3:
                realWorldGraphs();
                break;
            case 4:
                cout << "Closing the program..." << endl;
                break;
            default:
                cout << endl <<"Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 5);
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
                setGraphNormalFile("../projeto/data/real_world_graphs/shipping.csv");
                break;
            case 2:
                setGraphNormalFile("../projeto/data/toy_graphs/stadiums.csv");
                loadDataSet();
                break;
            case 3:
                setGraphNormalFile("../projeto/data/toy_graphs/tourism.csv");
                break;
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
                break;
            case 50:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_50.csv");
                break;
            case 75:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_75.csv");
                break;
            case 100:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_100.csv");
                loadDataSet();
                break;
            case 200:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_200.csv");
                break;
            case 300:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_300.csv");
                break;
            case 400:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_400.csv");
                break;
            case 500:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_500.csv");
                break;
            case 600:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_600.csv");
                break;
            case 700:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_700.csv");
                break;
            case 800:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_800.csv");
                break;
            case 900:
                setGraphNormalFile("../projeto/data/medium_graphs/edges_900.csv");
                break;
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
                loadDataSet();
                break;
            case 2:
                setGraphLargeFile("../projeto/data/real_world_graphs/graph2");
                break;
            case 3:
                setGraphLargeFile("../projeto/data/real_world_graphs/graph3");
                break;
            case 4:
                cout << "Returning..." << endl;
                return;
            default:
                cout << endl << "Invalid option. Choose again." << endl;
        }

        cout << endl;
    } while (choice != 4);
}


