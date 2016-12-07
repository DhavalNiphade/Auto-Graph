//
// Created by Dhaval on 11/23/2016.
//

#ifndef AUTO_GRAPH_DAG_H
#define AUTO_GRAPH_DAG_H

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

typedef pair<pair<unsigned int, unsigned int>, unsigned int> edge;

struct node {
    unsigned int label; //ID of the string associated with the arc
    unsigned int target; //ID of the node the arc points to
};

class DAG {

public:

    DAG(); //Constructor

    void addAttributeValue (unsigned int NodeID, unsigned int attribute, unsigned int value);
    void addAttributeValue (unsigned int NodeID, string attribute, string value);

    unsigned int addEdge(unsigned int from, unsigned int to);   //Used when adding edges
    unsigned int addTerminalEdge(unsigned int from, unsigned int label, unsigned int terminal); //used for leaf nodes
    unsigned int addEdgeToAll(unsigned int, unsigned int);

    void deleteEdge();  //used for the unification process

    //Printing and File functions
    string getDOT();
    //void toDOT();
    void saveDOTtoFile(string);


    map<pair<unsigned int, unsigned int>, unsigned int> graph; //Holds the actual graph associations
    map<unsigned int, unsigned int> links;
    map<pair<unsigned int, unsigned int>, unsigned int> pathValue; //Holds the integer values associated with the paths

    static unsigned int rootNodeId; //Initialized with 1. It stores the first node of the graph

    float getProbability();
    unsigned int getCount();

    void setCount(unsigned int);
    void setProbability(float);

    PathMapper pathStore;   //used for edge generation
    SymbolMapper symbolStore;   //used for symbol to integer conversions

    DAG unify(DAG); //Unification algorithm

private:

    float probability; //Probability of the DAG
    unsigned int count; //Number of DAGs

};


#endif //AUTO_GRAPH_DAG_H
