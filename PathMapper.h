//
// Created by Dhaval on 11/23/2016.
//

#ifndef AUTO_GRAPH_PATHMAPPER_H
#define AUTO_GRAPH_PATHMAPPER_H

#include <iostream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

class PathMapper {

public:

    void addPath(unsigned int, unsigned int, unsigned int);
    unsigned int addPath(unsigned int, unsigned int);

private:

    map<pair<unsigned int, unsigned int>, unsigned int> paths; //Used to store paths
    unsigned int lastState = 1;

};

#endif //AUTO_GRAPH_PATHMAPPER_H
