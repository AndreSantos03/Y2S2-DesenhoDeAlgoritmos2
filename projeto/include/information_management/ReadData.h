//
// Created by NASA on 21/05/2023.
//

#ifndef DA_PROJECT2_READDATA_H
#define DA_PROJECT2_READDATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include "../graph/Graph.h"


using namespace std;

class ReadData {
public:
    ReadData();
    static Graph readNormalGraph(const string &filename);
    static Graph readLargeGraph(const string &filename);
};


#endif //DA_PROJECT2_READDATA_H
