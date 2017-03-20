/*************************************************************************
 > File Name: Genetic.h
 > Author: Qian yuhui
 > Email: yhqian1017@gmail.com
 > Created Time: Mon 20 Mar 2017 09:14:11 PM CST
************************************************************************/

#ifdef __GENETIC_H__
#define __GENETIC_H__

#include <vector>
#include "graph.h"

class Result
{
public:
    int routeNum;
    vector<int> server;
    vector<list<int>> route; 
public:
    Result();
};

// 个体
class Gene
{
public:
    vector<int> server;
};

class Genetic
{
private:
    int _totalNumber;// 种群总数量
    int _deleteNumber;// 每次迭代别删除的数量
    int _crossNumber;// 一次交叉参与数
    vector<double> _veriationProbability// 变异概率
    static const int MAXITERATOR = 1000;// 多少次最优解不变则停止迭代

private:
    Gene _best;// 记录当前的最优解
    vector<vector<int>> _gene; //所有基因序列

private:
    double _Gamble(); //轮盘赌
    void _Select(); //选择
    void _CrossCover(); //杂交
    void _Variation(); //变异

public:
    Genetic(Graph rawGraph, vector<vector<int>> initServer);
    Result Optimize();
};

#endif
