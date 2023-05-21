//
// Created by NASA on 21/05/2023.
//

#include "../../include/information_management/ReadData.h"

Graph ReadData::readToyGraph(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename <<  endl << endl;
    }

    string fileLine;
    getline(file, fileLine); // skip the first line (column headers)

    while(getline(file, fileLine)){
    }
}
