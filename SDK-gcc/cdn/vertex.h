//节点类
class V{
private:
    int requireBandwidth;//需求的总流量
    int isServer;//部署服务器则设置为１
    int isClient;//属于消费节点则设置为０
    int inCapability;//流入当前节点的最大流量
    int outCapability;//流出当前节点的最大流量

public:
    V();
    //设置消费节点相关参数
    void setClient(int reqBandwidth);
    //设置服务器节点相关参数
    void setServer();
    //取消该节点为服务器的设置
    void resetServer();

    void setCapability(int inCap, int outCap);
    void setInCapability(int inCap);
    void setOutCapability(int outCap);

}