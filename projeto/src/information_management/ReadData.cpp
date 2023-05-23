//
// Created by NASA on 21/05/2023.
//

#include "../../include/information_management/ReadData.h"

ReadData::ReadData() {}


Graph ReadData::readToyGraph(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "File can not be opened";
    }
    Graph graph;

    string fileLine;
    getline(file, fileLine); // skip the first line (column headers)

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
                Vertex* vertex1 = new Vertex(origem);
                graph.addVertex(vertex1);
            }
            if(!graph.findVertex(destino)){
                Vertex* vertex2 = new Vertex(destino);
                graph.addVertex(vertex2);
            }

            graph.addEdge(origem,destino,distancia);
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
                Vertex* vertex1 = new Vertex(origem,labelOrigem);
                graph.addVertex(vertex1);
            }
            if(!graph.findVertex(destino)){
                Vertex* vertex2 = new Vertex(destino,labelDestino);
                graph.addVertex(vertex2);
            }

            graph.addEdge(origem,destino,distancia);
        }
    }

    return graph;
}

