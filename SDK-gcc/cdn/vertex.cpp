#include "vertex.h"

V::V(){
    requireBandwith = 0;
    isServer = 0;
    isClient = 0;
}

void V::setClient(int reqBandwidth){
    isClient = 1;
    requireBandwidth = reqBandwidth;
}

void V::setServer(){
    isServer = 1;
}

void V::resetServer(){
    isServer = 0;
}

void V::addEdge(E edge){
    Edge.push_back(edge);
}

E V::findEdge(int Dest){
    for(vector <E>::iterator it = Edge.begin(); it != Edge.end(); it++){
        if((*it.dest) == Dest){
            return *it;
        }
    }
    return E();
}


void V::setCapability(int inCap, int outCap){
    inCapability = inCap;
    outCapability = outCap;
}

void V::setInCapability(int inCap){
    inCapability = inCap;
}

void V::setOutCapability(int outCap){
    outCapability = outCap;
}





