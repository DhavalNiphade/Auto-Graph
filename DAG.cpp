//
// Created by Dhaval on 11/23/2016.
//

#include <DAG.h>
#include <utility>

unsigned int DAG::rootNodeId = 1;

DAG :: DAG (){
    //Do not initiate the DAG with anything
};

void addAttributeValue (unsigned int NodeID, unsigned int attribute, unsigned int value){};
void addAttributeValue (unsigned int NodeID, string attribute, string value){};

unsigned int DAG::addEdge(unsigned int from, unsigned int to){
    pair<unsigned int, unsigned int> key(from, to);
    map<pair<unsigned int, unsigned int>, unsigned int>::iterator it; //Initialize the iterator
    it=graph.find(key); //Set iterator to the point where the edge needs to be added

    if(it==graph.end()){
        //If edge is not found add a new state and add an edge to it
        unsigned int nextState = addEdgeToAll(from, label);
        return(nextState);
    }
    return(graph[key]);

}

unsigned int DAG::addTerminalEdge(unsigned int from, unsigned int label, unsigned int terminal){

    unsigned int tempTo = addEdge(from, label);
    pair<unsigned int, unsigned int> key(tempTo, label);
    map<pair<unsigned int, unsigned int>, unsigned int>::iterator it; //Initialize the iterator
    it=graph.find(key);
    if(it==graph.end()){
        //No terminal edge exists
        addEdgeToAll(temptTo, 0, terminal);
    }
    return(from);
}

unsigned int DAG::addEdgeToAll(unsigned int from, unsigned int label){
    unsigned int to = pathStore.addPath(from, label);
    graph[(from, label)] = to;
    pathValue[(from, to)] = label;
    return(to);
}

void DAG::deleteEdge(){

};

string DAG::getDOT(){
    stringstream ss;
    ss << "digraph DAG {" <<endl << "rankdir=TB;" << endl << endl;
    pair<unsigned int, unsigned int> key;
    for(auto const &edge : graph){ //range based loop over the graph
        key = edge.first;
        if(edge.second == 0)
            ss << key.first <<"[label=\"" << symbolStore.getLabel(key.second) << "\];" << endl;
        else
            ss << key.first << "->" << edge.second << "[label=\"" << symbolStore.getLabel(key.second) << "\];" << endl;
    }
    for(auto const &edge : links) {
        ss << edge.first << "->" << edge.second << "[style=dotted];" << endl;
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

string edgeToString(edge myEdge){
    stringstream ss;
    ss << myEdge.first.first << " " << myEdge.second << " " << DAG::symbolStore.getLabel(myEdge.first.second);
    return ss.str();

}


DAG DAG::unify(DAG otherDAG){
    DAG myDAG(*this);
        map<pair<unsigned int, unsigned int>, unsigned int>::iterator it;

    for (auto const &dedge: otherDAG.graph){
        cout << "Other edge : " << edgeToString(dedge) << endl;
        pair<unsigned int, unsigned int> fromTo = pair<unsigned int, unsigned int>(dedge.first.first, dedge.second);
        it = myDAG.pathValue.find(fromTo);
        if(it!=myDAG.pathValue.end()){
            if(dedge.first.second == myDAG.pathValue[fromTo]){
                cout << "This edge : " << edgeToString(edge(pair<unsigned int, unsigned int>(it->first.first,it->second),it->first.second)) << endl;
            }
        }
        else {
            cout << "No this edge....." << endl;
            myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
        }

        if(dedge.second==0){

            if(myDAG.graph.find(dedge.first) != myDAG.graph.end()){
                if(myDAG.graph[dedge.first]==0){
                    continue;
                }
                else{
                    cout << "Unification failed : path mis-match" << endl;
                    return DAG();
                }
            }
            else{
                fromTo = pair <unsigned int, unsigned int> (dedge.first.first,dedge.second);
                if(myDAG.pathValue.find(fromTo) != myDAG.pathValue.end()){
                    cout << "Unification failed : Terminal merging error with " << dedge.first.first << " " << dedge.second << DAG::symbolStore.getLabel(myDAG.pathValue[fromTo]) << endl;
                    return DAG();
                }
                myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
            }
        } else { //path
            fromTo = pair <unsigned int, unsigned int>(dedge.first.first, dedge.second);
            if(myDAG.graph.find(dedge.first)==myDAG.graph.end()){
                //not found
                myDAG.addEdgeToAll(dedge.first.first, dedge.second, dedge.first.second);
            }
        }
    }
    return myDAG;
}

bool DAG::addLink(unsigned int from , unsigned int to){
    //target node must have some continuation
    //from node cannot have a continuation
    links[from] = to;
}


//Functions for getting and setting probability
float getProbability(){
    return probability;
}

void setProbability(float p){
    DAG::probability = p;
}

//Functions for getting and setting count
unsigned int getCount(){
    return count;
}
void setCount(unsigned int c){
    DAG::count = c;
}