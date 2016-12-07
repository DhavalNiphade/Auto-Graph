//
// Created by Dhaval on 11/23/2016.
//

#ifndef AUTO_GRAPH_SYMBOLMAPPER_H
#define AUTO_GRAPH_SYMBOLMAPPER_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <utility>

using namespace std;

class SymbolMapper {

public:

    unsigned int getID(string); //function for inserting or fetching ID of a string that's already in symbol2int
    string getLabel(unsigned int);  //function for fetching the string value from a given ID

private:

    map<unsigned int, string> symbol2int; //Hash table to store string to int conversions
    map<string, unsigned int> int2symbol;   //Hash table to store int to string conversions

};


#endif //AUTO_GRAPH_SYMBOLMAPPER_H
