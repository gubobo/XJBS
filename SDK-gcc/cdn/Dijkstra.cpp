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

Path Dijkstra::SearchPath(vector<V> &table, int &start)
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
        present = _FindNext();
        if (present != noVertex) isDone = 1;
    }

    return _path;
}

vector<Path> Dijkstra::ServerPath(Graph graph)
{
    int i;
    vector<Path> pathTable(graph.server.size());
    for (i = 0; i < graph.server.size(); ++i)
    {
        pathTable[i] = SearchPath(graph.Table, graph.server[i].sequenceNumber);
    }
    return pathTable;
}

vector<Path> Dijkstra::ClientPath(Graph graph)
{
    int i;
    vector<Path> pathTable(graph.client.size());
    for (i = 0; i < graph.client.size(); ++i)
    {
        pathTable[i] = SearchPath(graph.Table, graph.client[i].sequenceNumber);
    }
    return pathTable;
}

int Dijkstra::_FindNext()
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
