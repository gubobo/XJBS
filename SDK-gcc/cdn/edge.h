#ifndef __EDGE_H__
#define __EDGE_H__

#define INFINITE 99999
#define MAX_BANDWIDTH INFINITE
#define MAX_COST INFINITE

struct E{
    int totalBandwith;//总带宽
    int remainedBandwidth;//剩余带宽
    int perCost;//带宽单价
    int dest;//边节点

    E();
    //设置链路总带宽和带宽单价
    void setEdge(int TotalBandwidth, int PerCost, int Dest);
    //消耗带宽
    bool consumeBandwidth(int bandwidth);

};

#endif


/*
//有向边
class E{
public:
    int totalBandwith;//总带宽
    int remainedBandwidth;//剩余带宽
    int perCost;//带宽单价

    E();
    //设置链路总带宽和带宽单价
    void setEdge(int TotalBandwidth, int PerCost);
    //消耗带宽
    bool consumeBandwidth(int bandwidth);
}
*/