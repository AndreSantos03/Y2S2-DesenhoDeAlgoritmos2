#include "../include/Menu.h"
#include <iostream>
#include <limits>

using namespace std;


Menu::Menu() : algorithms(graph) {
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
        cout << "3. Triangle 2-Approximation Algorithm" << endl;
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
                    clock_t start = clock();
                    double value = algorithms.primMST();
                    clock_t end = clock();
                    cout << "The graph has a minimum distance of: " << value << "." << endl;
                    cout << "The execution time was: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << endl;
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
    clock_t start = clock();
    Vertex* src = graph.findVertex(0);
    vector<bool> visited;
    vector<int> min_path;
    vector<int> curr_path;
    for(int i=0;i<graph.getVertexSet().size();i++){
        visited.push_back(false);
    }
    int count=0;
    double weight=0.0;
    double min_weight=numeric_limits<double>::max();

    clock_t end = clock();

    double minDistance = algorithms.backtracking(src, visited, count, weight, min_weight, src, min_path, curr_path);
    cout << endl << "The graph has a minimum distance of: " << minDistance <<"."<< endl;
    cout << "The execution time was: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << endl;
    cout << "The path is: ";
    for (int i = 0; i < min_path.size(); i++) {
        cout << min_path[i];
        if (i != min_path.size() - 1) {
            cout << " ==> ";
        }
    }
    cout << endl;
}

void Menu::otherHeuristicsMenu() {
    int choice;
    while (true) {
        cout << "=============== Other Heuristics ===============" << endl;
        cout << "1. Cluster Based Algorithm" << endl;
        cout << "2. Christofides Algorithm" << endl;
        cout << "4. Return" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                while (true) {
                    cout << "Choose number of clusters: ";
                    int clusterNum;
                    cin >> clusterNum;
                    vector<Vertex*> path = algorithms.clusterBasedAlgorithm(clusterNum);
                    for (auto v : path) {
                        cout << v->getId() << endl;
                    }
                    break;
                }
                break;
            }
            case 2: {
                clock_t start = clock();
                vector<Vertex*> path = algorithms.christofidesTSP();
                clock_t end = clock();
                cout << "The execution time was: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << endl;
                for (int i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i != path.size() - 1) {
                        cout << " ==> ";
                    }
                }
            }
            case 3: {
                return;
            }
            case 4:
                cout << "Returning..." << endl;
                break;
            default: {
                cout << "Invalid option. Choose again." << endl;
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

