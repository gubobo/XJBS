/*************************************************************************
 > File Name: Dijkstra.h
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Sun 19 Mar 2017 06:25:27 PM CST
************************************************************************/

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__ 

#include <list>
#include <vector>
#include "graph.h"

using std::list;
using std::vector;

// 记录一下用dijkstra算法寻找到的最佳路径
struct Path
{
    int start;
    vector<int> leastCost;
    vector<int> previous;
};

// 最短路径算法
class Dijkstra
{
private:
    static const int MAXCOST = 1000000; //线路不存在
    static const int noVertex = -1; //点不存在

private:
    int _vertexNumber;

    Path _path;
    vector<int> _usedVertex;

private:
    int _FindNext();

public:
    Dijkstra(int number);

    // 寻找单源最短路
    Path SearchPath(vector<V> &table, int &start);

    // 寻找从所有服务器节点出发的最短路径
    vector<Path> ServerPath(Graph graph);

    // 寻找从所有消费节点出发的最短路径
    vector<Path> ClientPath(Graph graph);
};

#endif //__DIJKSTRA_H__
