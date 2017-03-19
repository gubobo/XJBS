#include "edge.h"

E::E(){
    totalBandwidth = 0;
    remainedBandwidth = 0;
    perCost = MAX_COST;
}
    
//设置链路总带宽和带宽单价
void E::setEdge(int TotalBandwidth, int PerCost){
    totalBandwidth = TotalBandwidth;
    remainedBandwidth = totalBandwidth;
    perCost = PerCost;
}


//消耗带宽，成功返回true,失败返回false
bool E::consumeBandwidth(int bandwidth){
    if(bandwidth > remainedBandwidth){
        return false;
    }else{
        remainedBandwidth = remainedBandwidth - bandwidth;
        return true;
    }
}
