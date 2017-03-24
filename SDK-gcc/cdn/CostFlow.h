/*************************************************************************
 > File Name: CostFlow.h
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Tue 21 Mar 2017 12:32:36 AM CST
************************************************************************/

#ifndef __COSTFLOW_H__
#define __COSTFLOW_H__

#include <vector>
#include <list>
#include "graph.h"
#include "Dijkstra.h"

using std::vector;
using std::list;

class Solution
{
public:
    bool isWork; //是否可行
    int totalCost; // 总花费
    int pathNumber; // 总线路数目
    vector<list<int>> path; //所有路径
    vector<int> server; // 服务器设置
    vector<int> serverFlow; // 每个服务器提供的流量

    bool operator < (const Solution &s) const
    {
        return totalCost < s.totalCost;
    }
};

// 在已知了消费节点和服务器节点的情况下寻找最小费用流
class CostFlow
{
private:
    Graph _graph;

private:
    Solution _result;
    vector<Pair> _costPair;

public:
    CostFlow();
    Solution FindPath(Graph graph); // 寻找所有路径对
    void DelMiniFlow(); // 一条路线上的最小流量
};

#endif
