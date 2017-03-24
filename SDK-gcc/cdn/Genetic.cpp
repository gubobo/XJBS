/*************************************************************************
 > File Name: Genetic.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Mon 20 Mar 2017 10:23:52 PM CST
************************************************************************/

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "Dijkstra.h"
#include "Genetic.h"

Genetic::Genetic(Graph rawGraph, vector<vector<int>> initServer)
{
    _graph = rawGraph;
}

Solution Genetic::Optimize()
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

void Genetic::_select()
{
    int i;
    vector<Solution> allResult;
    CostFlow n;

    for (i = 0; i < _totalNumber; ++i)
    {
        allResult[i] = n.FindPath(_graph);
    }

    std::sort(allResult.begin(), allResult.end());
}

void Genetic::_CrossCover()
{
    
}

void Genetic::_Variation()
{
    
}
