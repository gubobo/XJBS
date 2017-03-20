/*************************************************************************
 > File Name: Genetic.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Mon 20 Mar 2017 10:23:52 PM CST
************************************************************************/

#include <cmath>
#include <cstdlib>
#include "Dijkstra.h"
#include "Genetic.h"

Genetic::Genetic(Graph rawGraph, vector<vector<int>> initServer)
{
    
}

Result Genetic::Optimize()
{
    bool isBetter = 1;
    int count = 0;
    Gene tmp = _best;
    while(isBetter)
    {
        _Select();
        _CrossCover();
        _Variation();

        if (tmp == _best) ++count;
        else 
        {
            count = 0; 
            tmp = _best;
        }
        
        if (count == MAXITERATOR)
            isBetter = 0;
    }
}
