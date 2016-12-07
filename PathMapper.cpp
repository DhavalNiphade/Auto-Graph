//
// Created by Dhaval on 11/23/2016.
//

#include "PathMapper.h"

void PathMapper::addPath(unsigned int from, unsigned int label, unsigned int terminal){

    unsigned int tempTo = addPath(from, label);
    pair<unsigned int, unsigned int> key(tempTo, terminal);

    if(paths.find(key)== paths.end()){
        //if transition is not there, add a terminal node
        //Thus, the definition now changes to (from, label, 0)
        paths[key]=0;
    }
}

unsigned int PathMapper::addPath(unsigned int from, unsigned int label){

    pair<unsigned int, unsigned int> key(from, label); //Store from and label as pairs to find in the paths table.
    if(paths.find(key)==paths.end()) {
        //if transition doesn't exist
        paths[key]=++lastState;
        return (lastState);
    }
    return(paths[key]);
}