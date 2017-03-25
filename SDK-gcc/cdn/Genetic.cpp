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
    srand(unsigned(time(NULL)));

    _totalNumber = 60;
    _deleteNumber = 20;

    _graph = rawGraph;
    _best.isWork = 0;
    _best.totalCost = Dijkstra::MAXCOST;
}

Solution Genetic::Optimize()
{
    bool isBetter = 1;
    int count = 0;

    // 记录一下当前最优解
    Solution tmp = _best;
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
        
        // 如果达到解不变的最大次数，那么停止循环
        if (count == MAXITERATOR)
            isBetter = 0;
    }
    return _best;
}

void Genetic::_Select()
{
    int i;
    vector<Solution> allResult;
    CostFlow n;

    for (i = 0; i < _totalNumber; ++i)
    {
        allResult[i] = n.FindPath(_graph);
    }

    std::sort(allResult.begin(), allResult.end());
    if (allResult[0].totalCost < _best.totalCost)
        _best = allResult[0];
}

void Genetic::_CrossCover()
{
    // 选择两两交配
    int i;
    // 取前三分之二交配 得到的子代覆盖后三分之二
    for (i = 0; i < _totalNumber * 2 /3 ; i += 2)
    {
        _gene[_totalNumber - _deleteNumber + i] = _merge(i);
    }
}

void Genetic::_Variation()
{
    int i;
    list<specialNode>::iterator iter;
    for (i = 0; i < _totalNumber; ++i)
    {
        for (iter = _gene[i].server.begin(); iter != _gene[i].server.end(); ++iter)
            if (_randReal() < _veriationProbability[i])
                (*iter) = _getNewVertex(i);
    }
}

double Genetic::_randReal()
{
    return rand() / RAND_MAX;
}

specialNode Genetic::_getNewVertex(int i)
{
    int tmpVertex;
    list<specialNode>::iterator iter;

    bool isNoRepeat = 0;
    while(!isNoRepeat)
    {
        tmpVertex = rand() % _graph.vertexNumber;

        isNoRepeat = 1;
        for (iter = _gene[i].server.begin(); iter != _gene[i].server.end(); ++i)
            if ((*iter).relevantNumber == tmpVertex)
                isNoRepeat = 0;
    }
    return specialNode(tmpVertex);
}

Gene Genetic::_merge(int i)
{
    
}
