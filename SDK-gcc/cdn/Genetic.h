/*************************************************************************
 > File Name: Genetic.h
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Mon 20 Mar 2017 09:14:11 PM CST
************************************************************************/

#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <vector>
#include "graph.h"
#include "CostFlow.h"

class Genetic
{
private:
    int _totalNumber;// 种群总数量
    int _deleteNumber;// 每次迭代别删除的数量
    vector<double> _veriationProbability; // 变异概率
    static const int MAXITERATOR = 100;// 多少次最优解不变则停止迭代

private:
    Solution _best;// 记录当前的最优解
    vector<Solution> _gene; //所有基因序列

    Graph _graph;

private:
    void _Select(); //选择
    void _CrossCover(); //杂交
    void _Variation(); //变异

    double _randReal(); //生成随机小数
    void _merge(int i); //归并排序
    specialNode _getNewVertex(int i); // 获取一个新的服务器点

public:
    Genetic(Graph rawGraph, vector<list<specialNode>> initServer);
    Solution Optimize();
};

#endif
