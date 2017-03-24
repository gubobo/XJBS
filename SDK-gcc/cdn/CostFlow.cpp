/*************************************************************************
 > File Name: CostFlow.cpp
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Tue 21 Mar 2017 12:32:48 AM CST
************************************************************************/

#include "CostFlow.h"
#include <algorithm>

CostFlow::CostFlow()
{

}

Solution CostFlow::FindPath(Graph graph)
{
    int i, j;

    Dijkstra n(graph);

    _costPair = n.ServerPath();
    while(_costPair[0].cost != Dijkstra::MAXCOST)
    {
        std::sort(_costPair.begin(), _costPair.end());
        DelMiniFlow();
        _costPair = n.ServerPath();
    }

    return _result;
}

void CostFlow::DelMiniFlow()
{
    int miniFlow = 10000;
    int presentVertex = _costPair[0].client;
    int previousVertex = _costPair[0].client;

    while (presentVertex != _costPair[0].server)
    {
        previousVertex = presentVertex;
        presentVertex = _costPair[0].previous[presentVertex];
        if (miniFlow > _graph.Table[presentVertex].Edge[_graph.edgenum[presentVertex][previousVertex]].remainedBandwidth)
            miniFlow = _graph.Table[presentVertex].Edge[_graph.edgenum[presentVertex][previousVertex]].remainedBandwidth;
    }

    presentVertex = _costPair[0].client;
    while (presentVertex != _costPair[0].server)
    {
        previousVertex = presentVertex;
        presentVertex = _costPair[0].previous[presentVertex];
        if (_graph.Table[presentVertex].Edge[_graph.edgenum[presentVertex][previousVertex]].remainedBandwidth -= miniFlow);
        else 
        {
            _graph.Table[presentVertex].Edge.erase(_graph.edgenum[presentVertex][previousVertex]);
        }
    }
}
