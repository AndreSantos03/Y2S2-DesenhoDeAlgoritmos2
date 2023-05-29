//
// Created by diogo on 29/05/2023.
//

#include "../include/Menu.h"
#include <iostream>

using namespace std;


Menu::Menu() : algorithms(graph) {
    data = ReadData();
    graph = data.readNormalGraph("../projeto/data/toy_graphs/shipping.csv");
    algorithms = Algorithms(graph);
}



void Menu::display() {
    int choice;
    do {
        cout << "===== MENU =====" << endl;
        cout << "1. Load dataset" << endl;
        cout << "2. Remove Edge" << endl;
        cout << "3. Triangular Approximation Heuristic" << endl;
        cout << "4. Other Heuristics" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option:";
        cin >> choice;

        switch (choice) {
            case 1:
                loadDataSet();
                break;
            case 2:
                int choice2;
                cin >> choice2;
                graph.removeVertex(choice2);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opção inválida. Escolha uma opção válida." << endl;
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

