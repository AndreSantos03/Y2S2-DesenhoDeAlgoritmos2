//
// Created by NASA on 21/05/2023.
//

#include "../../include/information_management/ReadData.h"

ReadData::ReadData() = default;

Graph ReadData::readNormalGraph(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw filename + " cannot be opened";
    }
    Graph graph;

    string fileLine;
    if (filename.find("toy_graphs") != string::npos) {
        getline(file, fileLine); // skip the first line (column headers)
    }

    if (filename != "../projeto/data/toy_graphs/tourism.csv") {
        unordered_set<int> loadedInts;
        while (getline(file, fileLine)) {
            stringstream ss(fileLine);
            string sourceS, destS, distanceS;
            getline(ss, sourceS, ',');
            getline(ss, destS, ',');
            getline(ss, distanceS, ',');

            int source = stoi(sourceS);
            int dest = stoi(destS);
            double distance = stof(distanceS);

            if (loadedInts.find(source) == loadedInts.end()) {
                auto* vertex1 = new Vertex(source);
                graph.addVertex(vertex1);
                loadedInts.insert(source);
            }
            if (loadedInts.find(dest) == loadedInts.end()) {
                auto* vertex2 = new Vertex(dest);
                graph.addVertex(vertex2);
                loadedInts.insert(dest);
            }


            graph.addBidirectionalEdge(source, dest, distance);
        }
    } else {
        unordered_set<int> loadedInts;

        while (getline(file, fileLine)) {
            stringstream ss(fileLine);
            string sourceS, destS, distanceS, sourceLabel, destLabel;

            getline(ss, sourceS, ',');
            getline(ss, destS, ',');
            getline(ss, distanceS, ',');
            getline(ss, sourceLabel, ',');
            getline(ss, destLabel, ',');

            int source = stoi(sourceS);
            int dest = stoi(destS);
            double distance = stof(distanceS);

            if (loadedInts.find(source) == loadedInts.end()) {
                auto* vertex1 = new Vertex(source);
                graph.addVertex(vertex1);
                loadedInts.insert(source);
            }

            if (loadedInts.find(dest) == loadedInts.end()) {
                auto* vertex2 = new Vertex(dest);
                graph.addVertex(vertex2);
                loadedInts.insert(dest);
            }


            graph.addBidirectionalEdge(source, dest, distance);
        }
    }
    return graph;
}

Graph ReadData::readLargeGraph(const string &filename) {

    string fileNodesName = filename + "/nodes.csv";
    string fileEdgesName = filename + "/edges.csv";
    ifstream fileNodes(fileNodesName);
    ifstream fileEdges(fileEdgesName);
    if (!fileNodes.is_open()) {
        throw fileNodesName + " cannot be opened!";
    }
    if (!fileEdges.is_open()) {
        throw fileEdgesName + " cannot be opened!";
    }
    Graph graph;

    string fileLine;
    getline(fileNodes, fileLine); // skip the first line (column headers)

    while (getline(fileNodes, fileLine)) {
        stringstream ss(fileLine);
        string idS, longitudeS, latitudeS;
        getline(ss, idS, ',');
        getline(ss, longitudeS, ',');
        getline(ss, latitudeS, ',');

        int id = stoi(idS);
        double longitude = stof(longitudeS);
        double latitude = stof(latitudeS);
        auto* v = new Vertex(id, longitude, latitude);
        graph.addVertex(v);
    }

    getline(fileEdges, fileLine); // skip the first line

    while (getline(fileEdges, fileLine)) {
        stringstream ss(fileLine);
        string sourceS, destS, distanceS;

        getline(ss, sourceS, ',');
        getline(ss, destS, ',');
        getline(ss, distanceS, ',');

        int source = stoi(sourceS);
        int dest = stoi(destS);
        double distance = stof(distanceS);
        graph.addBidirectionalEdge(source, dest, distance);
    }

    return graph;
}
