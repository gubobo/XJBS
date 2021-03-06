#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "edge.h"
#include "vertex.h"
#include <list>
#include <vector>
#include <string>

using std::list;
using std::vector;
using std::string;

//用于存储消费节点和服务器节点
class specialNode{
public:
    int sequenceNumber;// 节点序列号
    int relevantNumber;// 相连节点序列号

    int reqBandwidth; // 需求 客户使用
    int outBandwidth;// 流出当前节点的流量 服务器使用

    specialNode(int num = -1, int band = 0){
        sequenceNumber = -1;
        relevantNumber = num;
        reqBandwidth = band;
    }

    bool operator == (const specialNode &t) const
    {
        return relevantNumber == t.relevantNumber;
    }
    bool operator < (const specialNode &t) const
    {
        return outBandwidth < t.outBandwidth;
    }
};


// 记录一下用dijkstra算法寻找到的最佳路径
class Path
{
public:
    int start;
    //建图的时候对其进行了初始化
    vector<int> leastCost;
    vector<int> previous;

    Path(int vertexNumber, int maxcost, int novertex){
        leastCost = vector<int>(vertexNumber, maxcost); //默认花费无限大
        previous = vector<int>(vertexNumber, novertex); //前驱未知
    }
};

// 传输给最大流运算
class Pair
{
public:
    specialNode server;
    specialNode client;
    int cost;
    vector<int> previous;
    bool operator < (const Pair &c) const
    {
        return cost < c.cost;
    }
};



class Graph{

public:
    int vertexNumber;//节点数目
    int edgeNumber;//链路数目
    int costVertexNumber;//消费节点数目
    int singleServerCost;//视频内容服务器部署成本  

    //路径
    //Path path;
    //vector<int> usedVertex;

public:
    static const int MAXCOST = 1000000; //线路不存在
    static const int noVertex = -1; //点不存在

public:
    vector<vector<E>> edge;
    vector <V> Table;//邻阶表,每个元素含有一个自身节点
    vector <Path> clientPathTable;

    list <specialNode> client;//存储client的节点
    list <specialNode> server;//存储server的节点
    int * degree1;//每个节点的度(按照连接的边数来计算)
    int * degree2;//每个节点的度(按照连接的边上的总带宽来计算)

    int serverNumber;//服务器的总个数
    int center1;//图的中心
    int center2;//图的中央点
    long long deployCost; //部署的总成本
    //具有优先级的节点序列,二分查找寻找最佳节点数目及初始位置(暂时没更好的想法)
    vector <V> subTable;//通过生成树构造的子图,每个元素中含有一个自身的节点,可以对其进行排序
    
    Graph();
    ~Graph();
    //每次读取一个数值，并且跳过一个特殊字符，creatGraph的辅助函数
    int readNumber(char * & str);
    //计算每个节点的度
    void calculateDegree();
    //构造邻接矩阵,构造定点集合，记录client集合
    void creatGraph(char ** topo);
    //保存图于txt中，用于python图的可视化
    void saveGraph();
    //计算中心函数
    void calculateCenter1();
    //计算中央点函数
    void calculateCenter2();
    //返回从点i到center的下一个节点
    int nextNode(int i, int center);
    //根据trafic大小来生成节点的优先级
    void Max_T(int center);
    
    void clearServer();
    void setServer(int k);
    
    //
    int findNext(vector<bool> usedVertex, Path path);
    // 寻找单源最短路
    Path searchPath(int start, int end = noVertex);
    // 寻找从所有服务器节点出发的最短路径
    vector<Pair> serverPath();
    // 寻找从所有消费节点出发的最短路径
    vector<Path> clientPath();

};


#endif
