#include <iostream>
#include "include/information_management/ReadData.h"

using namespace std;

int main() {
    ReadData readData = ReadData();
   try{
        Graph graph = readData.readLargeGraph("../projeto/data/real_world_graphs/graph1");
        cout << "HERE" << endl;
        for(auto v : graph.getVertexSet()){
            cout << v->getId() << ":" << v->getAdj().size() <<endl;
        }
   }
   catch (char const* e){
       cout << e;
   }

}
