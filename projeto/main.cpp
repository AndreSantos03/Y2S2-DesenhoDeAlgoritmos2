#include <iostream>
#include "include/information_management/ReadData.h"

using namespace std;

int main() {
    ReadData readData = ReadData();
   try{
        Graph graph = readData.readToyGraph("../projeto/data/toy_graphs/tourism.csv");
        vector<Vertex *> s = graph.getVertexSet();
       for (Vertex* vertex : s) {
           cout << vertex->getId() << " : " << vertex->getLabel()<< endl;  // Access the member function inside each Vertex
       }
   }
   catch (char const* e){
       cout << e;
   }

}
