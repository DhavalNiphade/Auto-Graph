//
// Created by Dhaval on 11/23/2016.
// Used for generating a unique integer value for strings and vice versa
// Called while building a graph
//

#include "SymbolMapper.h"

using namespace std;

string SymbolMapper::getLabel(unsigned int labelID){
    if(int2symbol.find(labelID) == int2symbol.end()){
        printf("\n\rNo such value in memory. Please insert a value before calling it");
        return;
    }

    return(int2symbol[labeID]);
}

unsigned int SymbolMapper::getID(string symbol){
    if(symbol2int.find(symbol)== symbol2int.end()){
        unsigned int s = (unsigned int)symbol2int.size() + 1;
        symbol2int [symbol] = s;
        int2symbol [s] = symbol;
    }
    return ((unsigned int)SymbolMapper::symbol2int[symbol]);

}