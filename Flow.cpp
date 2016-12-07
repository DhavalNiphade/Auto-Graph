//
// Created by Dhaval on 11/27/2016.
//

#include "Flow.h"

using namespace std;

Flow(){
//Do not initialize a flow
};

int bfs(int startNode, int endNode){

    memset(parentList, NOTSET, sizeof(parentList));
    memset(pathCapacity, 0, sizeof(pathCapacity));

    queue<int> q;
    q.push(startNode);

    parentList[startNode]=-2;
    pathCapacity[startNode]=INF;

    while(!q.empty()){
        int currentNode = q.front();q.pop();

        for(int i=0; i<graph[currentNode].size(); i++){
            int to = graph[currentNode][i];
            if(parentList[to]==NOTSET){
                if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0) {
                    parentList[to] = currentNode;
                    pathCapacity[to] = min(pathCapacity[currentNode],
                                           capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if (to == endNode)
                        return pathCapacity[endNode];
                    q.push(to);
                }
            }
        }
    }
    return 0;
}

int edmondsKarp(int startNode, int endNode){

    int maxFlow = 0;

    while(true){
        int flow = bfs(startNode, endNode);

        if (flow==0){
            break;
        }

        maxFlow = maxFlow + flow;
        int currentNode = endNode;

        while(currentNode != startNode){
            int previousNode = parentList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;

            currentNode = previousNode;
        }
    }
    return maxFlow;
}

unsigned int Flow::addFlow(unsigned int from, unsigned int to, unsigned int capacity) {
    pair<unsigned int, unsigned int> key(from, to); //Create a pair to hold the association
    //for(map<pair<unsigned int, unsigned int>, unsigned int>::iterator it = flow.find(key) ; it != flow.end() ; it++){ }
    map<pair<unsigned int, unsigned int>, unsigned int>::iterator it = flow.find(key);

    if(it == flow.end()){
        //flow did not exist.
        //Add a new last node and assign a flow
        unsigned int nextNode = addFlowtoAll(from, capacity);
        return (nextNode);
    }
}

unsigned int Flow::addFlowtoAll(unsigned int from , unsigned int capacity){
    unsigned int to = pathStore.addPath(from, capacity);
    flow[(from, capacity)] = to;
    flowValues[(from, to)] = capacity;
};

unsigned int Flow::addTerminalFlow(unsigned int from, unsigned int capacity, unsigned int terminal) {
    unsigned int tempTo = addFlow(from, capacity);
    pair<unsigned int, unsigned int> key(tempTo,label);
    map<pair<unsigned int, unsigned int>, unsigned int>::iterator it;
    it = flow.find(key);
    if(it == flow.end()){
       addFlowtoAll(from, 0 , terminal);
    }
}

string DAG::getDOT(){
    stringstream ss;
    ss << "digraph DAG {" <<endl << "rankdir=TB;" << endl << endl;
    pair<unsigned int, unsigned int> key;
    for(auto const &route : flow){ //range based loop over the graph
        key = route.first;
        if(route.second == 0)
            ss << key.first <<"[label=\"" << symbolStore.getLabel(key.second) << "\];" << endl;
        else
            ss << key.first << "->" << edge.second << "[label=\"" << symbolStore.getLabel(key.second) << "\];" << endl;
    }
    for(auto const &route : parentMap) {
        ss << route.first << "->" << route.second << "[style=dotted];" << endl;
    }
    ss << "}" << endl;
    return ss.str();
}

void DAG::saveDOTtoFile(string fname){
    ofstream myfile;
    myfile.open(fname, ios::out);
    if(myfile.is_open()){
        myfile << DAG::getDOT() << endl;
    }
    myfile.close();
};
