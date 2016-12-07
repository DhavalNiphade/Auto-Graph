//
// Created by Dhaval on 11/27/2016.
//

#ifndef AUTO_GRAPH_FLOW_H
#define AUTO_GRAPH_FLOW_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include "PathMapper.h"
#include "SymbolMapper.h"
#include <queue>

#define NODES 1000  //Maximum number of nodes
#define INF  32627
#define NOTSET -1   //For nodes that dont have a parent

class Flow {

public:

    Flow(); //Constructor

    map<pair<unsigned int, unsigned int>, unsigned int > flow; //Stores in "from, capacity" -> "to" fashion
    map<pair<unsigned int, unsigned int>, unsigned int> flowValues; //Stores in "from, to" -> "capacity" fashion
    map<unsigned int, unsigned int> parentMap;

    unsigned int addFlow(unsigned int from, unsigned int to);
    unsigned int addFlowtoAll(unsigned int from, unsigned int capacity);
    unsigned int addTerminalFlow(unsigned int from, unsigned int capacity, unsigned int terminal);

    string getDOT();
    void toDOT();


    /*-----------------------------------------------------------------------------------------*/

    unsigned int bfs(int, int);
    unsigned int maxFlow(int, int);

    vector <unsigned int> graph[NODES];
    unsigned int parentList[NODES];
    unsigned int pathCapacity[NODES];

    unsigned int capacities[][NODES];
    int flowPassed [][NODES]; //since negative flow should be supported

    PathMapper pathStore;   //used for edge generation
    SymbolMapper symbolStore;   //used for symbol to integer conversions


private:



};


#endif //AUTO_GRAPH_FLOW_H
