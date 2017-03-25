#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "edge.h"
#include "vertex.h"
#include <vector>
using std::vector;

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
};

class Graph{

public:
    int vertexNumber;//节点数目
    int edgeNumber;//链路数目
    int costVertexNumber;//消费节点数目
    int singleServerCost;//视频内容服务器部署成本
    vector<vector<E>> edge;

public:
    vector <V> Table;//邻阶表,每个元素含有一个自身节点
    list <specialNode> client;//存储client的节点
    list <specialNode> server;//存储server的节点
    int * degree1;//每个节点的度(按照连接的边数来计算)
    int * degree2;//每个节点的度(按照连接的边上的总带宽来计算)

    int serverNumber;//服务器的总个数
    int center1;//图的中心
    int center2;//图的中央点
    vector <V> subTable;//通过生成树构造的子图,每个元素中含有一个自身的节点
    long long deployCost; //部署的总成本

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
    int calculateCenter1();
    //计算中央点函数
    int calculateCenter2();
    //计算最短路径生成树
    void SPT();
    //计算最小跨度生成树
    void MST();

    void Max_T();

    void Max_TD();

    void MIPP();

};


#endif
