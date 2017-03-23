/*************************************************************************
 > File Name: Dijkstra.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Sun 19 Mar 2017 07:29:37 PM CST
************************************************************************/

#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph graph)
{
    _graph = graph;
    _vertexNumber = graph.vertexNumber;
    _path.leastCost = vector<int>(_vertexNumber, MAXCOST); //默认花费无限大
    _path.previous = vector<int>(_vertexNumber, noVertex); //前驱未知
    _usedVertex = vector<int>(_vertexNumber, 0); //点都没用过
}

Path Dijkstra::SearchPath(int &start)
{
    int present = start;
    int tmpNext;
    int j;

    bool isDone = 0;

    _path.leastCost[present] = 0;
    _usedVertex[present] = 1;

    while(!isDone)
    {
        for (j = 0; j < _graph.Table[present].Edge.size(); ++j) 
        {
            tmpNext = _graph.Table[present].Edge[j].dest;
            if (_graph.Table[present].Edge[j].perCost + _path.leastCost[present] < _path.leastCost[j])
            {
                _path.leastCost[j] = _graph.Table[present].Edge[j].perCost + _path.leastCost[present];
                _path.previous[j] = present;
            }
        }
        present = _FindNext();
        if (present != noVertex) isDone = 1;
    }

    return _path;
}

vector<Path> Dijkstra::ServerPath()
{
    int i;
    vector<Path> pathTable(_graph.server.size());
    for (i = 0; i < _graph.server.size(); ++i)
    {
        pathTable[i] = SearchPath(_graph.server[i].sequenceNumber);
    }
    return pathTable;
}

vector<Path> Dijkstra::ClientPath()
{
    int i;
    vector<Path> pathTable(_graph.client.size());
    for (i = 0; i < _graph.client.size(); ++i)
    {
        pathTable[i] = SearchPath(_graph.client[i].sequenceNumber);
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
