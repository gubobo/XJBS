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
#include "vertex.h"

using std::list;
using std::vector;

struct Path
{
    int start;
    vector<int> leastCost;
    vector<int> previous;
};

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
    int FindNext();

public:
    Dijkstra(int number);
    void SearchPath(vector<V> &table, int &start);
    vector<int> GetCost();
    Path GetPath();
};

#endif //__DIJKSTRA_H__
