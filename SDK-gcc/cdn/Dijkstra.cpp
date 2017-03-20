/*************************************************************************
 > File Name: Dijkstra.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Sun 19 Mar 2017 07:29:37 PM CST
************************************************************************/

#include "Dijkstra.h"

Dijkstra::Dijkstra(int number)
{
    _vertexNumber = number;
    _path.leastCost = vector<int>(number, MAXCOST); //默认花费无限大
    _path.previous = vector<int>(number, noVertex); //前驱未知
    _usedVertex = vector<int>(number, 0); //点都没用过
}

vector<int> Dijkstra::GetCost()
{
    return _path.leastCost;
}

Path Dijkstra::GetPath()
{
    return _path;
}

void Dijkstra::SearchPath(vector<V> &table, int &start)
{
    int present = start;
    int tmpNext;
    int j;

    bool isDone = 0;

    _path.leastCost[present] = 0;
    _usedVertex[present] = 1;

    while(!isDone)
    {
        for (j = 0; j < table[present].Edge.size(); ++j) 
        {
            tmpNext = table[present].Edge[j].dest;
            if (table[present].Edge[j].perCost + _path.leastCost[present] < _path.leastCost[j])
            {
                _path.leastCost[j] = table[present].Edge[j].perCost + _path.leastCost[present];
                _path.previous[j] = present;
            }
        }
        present = FindNext();
        if (present != noVertex) isDone = 1;
    }
}

int Dijkstra::FindNext()
{
    int i = 0, j = noVertex;
    int tmp = MAXCOST;
    for (i = 0; i < _vertexNumber; ++i)
    {
        if (tmp < _path.leastCost[i] && !_usedVertex[i])
        {
            j = i;
            tmp = _path.leastCost[i];
        }
    }
    return j;
}
