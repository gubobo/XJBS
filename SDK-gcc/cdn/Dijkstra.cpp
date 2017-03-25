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
    _path.start = start;
    int tmpNext;
    list<int>::iterator i;

    bool isDone = 0;

    _path.leastCost[present] = 0;
    _usedVertex[present] = 1;

    while(!isDone)
    {
        for (i = _graph.Table[present].nextVertex.begin() ; i != _graph.Table[present].nextVertex.end(); ++i) 
        {
            tmpNext = *i;
            if (_graph.edge[present][*i].perCost + _path.leastCost[present] < _path.leastCost[*i])
            {
                _path.leastCost[*i] = _graph.edge[present][*i].perCost + _path.leastCost[present];
                _path.previous[*i] = present;
            }
        }
        present = _FindNext();
        if (present != noVertex) isDone = 1;
    }

    return _path;
}

vector<Pair> Dijkstra::ServerPath()
{
    list<specialNode>::iterator i, j;
    int k = 0;
    Path onePath;
    vector<Pair> costPair(_graph.server.size() * _graph.client.size());

    for (i = _graph.server.begin(); i != _graph.server.end(); ++i)
    {
        onePath = SearchPath((*i).relevantNumber);
        for (j = _graph.client.begin(); j != _graph.client.end(); ++j)
        {
            costPair[k].server.relevantNumber = onePath.start;;
            costPair[k].client.relevantNumber = (*j).relevantNumber;
            costPair[k].cost = onePath.leastCost[(*j).relevantNumber];
            costPair[k].previous = onePath.previous;
            ++k;
        }
    }
    return costPair;
}

vector<Path> Dijkstra::ClientPath()
{
    list<specialNode>::iterator i;
    int j = 0;
    vector<Path> pathTable(_graph.client.size());
    for (i = _graph.client.begin(); i != _graph.client.end(); ++i)
    {
        pathTable[j++] = SearchPath((*i).relevantNumber);
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
