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
        cout << "2. Backtracking Algorithm" << endl;
        cout << "3. Triangular Approximation Heuristic" << endl;
        cout << "4. Other Heuristics" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
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