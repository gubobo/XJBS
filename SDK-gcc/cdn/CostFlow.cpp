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
    _result.isWork = 0;
    _result.totalCost = 0;
    _result.pathNumber = 0;
}

Solution CostFlow::FindPath(Graph graph)
{
    // 初始化
    _graph = graph;
    _result.server = _graph.server;
    _result.totalCost = _graph.server.size() * _graph.singleServerCost;

    bool isEnd = 0;

    Dijkstra n(_graph);

    while (!isEnd)
    {
        n.init(_graph);
        // 寻找所有最短路径对
        _costPair = n.ServerPath();

        // 给路径对通过单位流量花费排序
        std::sort(_costPair.begin(), _costPair.end());

        // 如果有路径对
        if (_costPair[0].cost != MAXCOST)
            DelMiniFlow();
        // 没有路径对，找不到路径，就是这种取点不成立
        else if (_costPair[0].cost == MAXCOST)
        {
            _result.isWork = 0;
            isEnd = 1;
        }
        
        // 消费节点删除完毕，也就是都已经满足
        if (_graph.client.empty()) 
        {
            _result.isWork = 1;
            isEnd = 1;
        }
    }
    
    return _result;
}

void CostFlow::DelMiniFlow()
{
    int miniFlow = _costPair[0].client.reqBandwidth;
    int presentVertex = _costPair[0].client.relevantNumber;
    int previousVertex = _costPair[0].client.relevantNumber;
    
    // 找一下在最小花费路径上的带宽最小值
    while (presentVertex != _costPair[0].server.relevantNumber)
    {
        previousVertex = presentVertex;
        presentVertex = _costPair[0].previous[presentVertex];
        if (miniFlow > _graph.edge[presentVertex][previousVertex].remainedBandwidth)
            miniFlow = _graph.edge[presentVertex][previousVertex].remainedBandwidth;
    }
    
    // 如果带宽最小值比消费节点需求大，那么消费节点所需带宽就是
    // 这条路径上需要删除掉的带宽值
    // 反过来就是删除带宽最小值
    if (_costPair[0].client.reqBandwidth == miniFlow)
//    {
//        list<specialNode>::iterator i;
//        for (i = _graph.client.begin(); i != _graph.client.end(); ++i)
//            if ((*i).relevantNumber == _costPair[0].client.relevantNumber)
//                _graph.client.erase(i);
//    }
        _graph.client.remove(_costPair[0].client);
    else
        _costPair[0].client.reqBandwidth -= miniFlow;

    // 在这个循环里带宽删减
    // 如果出现删减到0的那么就把该路径去掉
    presentVertex = _costPair[0].client.relevantNumber;
    while (presentVertex != _costPair[0].server.relevantNumber)
    {
        previousVertex = presentVertex;
        presentVertex = _costPair[0].previous[presentVertex];
        if (_graph.edge[presentVertex][previousVertex].remainedBandwidth -= miniFlow);
        else 
        {
            _graph.Table[presentVertex].nextVertex.remove(previousVertex);
            _graph.Table[previousVertex].nextVertex.remove(presentVertex);
        }
    }
    
    // 路径+1
    ++_result.pathNumber;
    
    // 服务器提供的流量
    list<specialNode>::iterator i; 
    for (i = _result.server.begin(); i != _result.server.end(); ++i)
    {
        if ((*i).relevantNumber == _costPair[0].server.relevantNumber)
            (*i).outBandwidth += miniFlow;
    }
}
