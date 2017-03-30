/*************************************************************************
 > File Name: Genetic.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Mon 20 Mar 2017 10:23:52 PM CST
************************************************************************/

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "Genetic.h"

Genetic::Genetic(Graph rawGraph, vector<list<specialNode>> initServer)
{
    srand(unsigned(time(NULL)));

    _totalNumber = 30;
    _deleteNumber = 10;

    _graph = rawGraph;
    _best.isWork = 0;
    _best.totalCost = Graph::MAXCOST;
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
    CostFlow n;

    for (i = 0; i < _totalNumber; ++i)
    {
        _graph.server = _gene[i].server;
        _gene[i] = n.FindPath(_graph);
    }

    std::sort(_gene.begin(), _gene.end());
    if (_gene[0].totalCost < _best.totalCost)
        _best = _gene[0];

    for (i = _totalNumber - _deleteNumber; i < _totalNumber; ++i)
        _gene[i].server.clear();

}

void Genetic::_CrossCover()
{
    // 选择两两交配
    int i;
    // 取前三分之二交配 得到的子代覆盖后三分之二
    for (i = 0; i < _totalNumber * 2 /3 ; i += 2)
    {
        _merge(i);
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

void Genetic::_merge(int i)
{
    int gene1 = i;
    int gene2 = i + 1;    

    _gene[gene1].server.sort();
    _gene[gene2].server.sort();

    list<specialNode>::iterator iter1, iter2;
    iter1 = _gene[gene1].server.begin();
    iter2 = _gene[gene2].server.begin();
    
    int getNumber = 10; //这个要改
    while(getNumber--)
    {
        if ((*iter1).outBandwidth > (*iter2).outBandwidth)
            _gene[i + _totalNumber - _deleteNumber].server.push_back(specialNode((*iter1).relevantNumber));
        else
            _gene[i + _totalNumber - _deleteNumber].server.push_back(specialNode((*iter2).relevantNumber));
    }
}
