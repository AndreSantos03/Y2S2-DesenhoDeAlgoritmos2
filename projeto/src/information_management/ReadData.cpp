//
// Created by NASA on 21/05/2023.
//

#include "../../include/information_management/ReadData.h"

ReadData::ReadData() {}


Graph ReadData::readNormalGraph(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw filename + " can not be opened";
    }
    Graph graph;

    string fileLine;
    if(filename.find("toy_graphs") != string::npos) {
        getline(file, fileLine); // skip the first line (column headers)
    }

    if(filename != "../projeto/data/toy_graphs/tourism.csv"){
        while(getline(file, fileLine)){
            stringstream ss(fileLine);
            string origemS, destinoS, distanciaS;
            getline(ss,origemS,',');
            getline(ss,destinoS,',');
            getline(ss,distanciaS,',');

            int origem = stoi(origemS);
            int destino = stoi(destinoS);
            double distancia = stof(distanciaS);


            if(!graph.findVertex(origem)){
                Vertex vertex1 = Vertex(origem);
                graph.addVertex(&vertex1);
            }
            if(!graph.findVertex(destino)){
                Vertex vertex2 = Vertex(destino);
                graph.addVertex(&vertex2);
            }

            graph.addBidirectionalEdge(origem,destino,distancia);
        }
    }
    else{
        while(getline(file, fileLine)){
            stringstream ss(fileLine);
            string origemS, destinoS, distanciaS,labelOrigem, labelDestino;

            getline(ss,origemS,',');
            getline(ss,destinoS,',');
            getline(ss,distanciaS,',');
            getline(ss,labelOrigem,',');
            getline(ss,labelDestino,',');

            int origem = stoi(origemS);
            int destino = stoi(destinoS);
            double distancia = stof(distanciaS);


            if(!graph.findVertex(origem)){
                Vertex vertex1 = Vertex(origem,labelOrigem);
                graph.addVertex(&vertex1);
            }
            if(!graph.findVertex(destino)){
                Vertex vertex2 = Vertex(destino,labelDestino);
                graph.addVertex(&vertex2);
            }

            graph.addBidirectionalEdge(origem,destino,distancia);
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
        throw fileNodesName + " can not be opened!";
    }
    if (!fileEdges.is_open()) {
        throw fileNodesName + " can not be opened!";
    }
    Graph graph;

    string fileLine;
    getline(fileNodes, fileLine); // skip the first line (column headers)

    while(getline(fileNodes,fileLine)){
        stringstream ss(fileLine);
        string idS, longitudeS, latitudeS;
        getline(ss,idS,',');
        getline(ss,longitudeS,',');
        getline(ss,latitudeS,',');

        int id = stoi(idS);
        double longitude = stof(longitudeS);
        double latitude = stof(latitudeS);
        Vertex v = Vertex(id,longitude,latitude);
        graph.addVertex(&v);
    }


    getline(fileEdges, fileLine); //skip the first line

    while(getline(fileEdges,fileLine)){
        stringstream ss(fileLine);
        string origemS, destinoS, distanciaS;

        getline(ss,origemS,',');
        getline(ss,destinoS,',');
        getline(ss,distanciaS,',');

        int origem = stoi(origemS);
        int destino = stoi(destinoS);
        double distancia = stof(distanciaS);
        graph.addBidirectionalEdge(origem, destino,distancia);
    }
    return graph;
}



