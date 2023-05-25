#include <iostream>
#include "include/information_management/ReadData.h"
#include "include/graph/Algorithms.h"

using namespace std;

int main() {
    ReadData readData = ReadData();
   try{
       Graph graph = readData.readNormalGraph("../projeto/data/toy_graphs/shipping.csv");
       Algorithms algorithms = Algorithms(graph);
   }
   catch (char const* e){
       cout << e;
   }

}
