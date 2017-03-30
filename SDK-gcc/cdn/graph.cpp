#include "graph.h"
#include "lib_io.h"

#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
using std::string;
using std::stack;
using std::cout;
using std::sort;

Graph::Graph(){
}

Graph::~Graph(){
}

int Graph::readNumber(char * & str){
    int number = 0;
    while((*str)>='0' && (*str)<='9'){
        number = number * 10;
        number += *str - '0';
        str++;
    }
    //只跳过一个特殊符号
    if((*str)=='\n'||(*str)==' '){
        str++;
    }
    return number;
}

void Graph::calculateDegree(){
    degree1 = new int [vertexNumber];
    degree2 = new int [vertexNumber];
    for(int i=0; i<vertexNumber; i++){
        degree1[i] = 0;
        degree2[i] = 0;
    }
    for(int i=0; i<vertexNumber; i++){
        degree1[i] = edge[i].size();
        for(int j=0; j<degree1[i]; j++){
            degree2[i] += edge[i][j].totalBandwidth;
        }
    }
}

void Graph::creatGraph(char ** topo){
    int line = 0;//指示行号
    char * p;
    p = topo[line];
    vertexNumber = readNumber(p);//网络节点数目
    edgeNumber = readNumber(p);//网络链路数目
    costVertexNumber = readNumber(p);//消费节点数目
    line += 2;
    p = topo[line];
    singleServerCost = readNumber(p);//视频内容服务器部署成本
    line += 2;
    p = topo[line];

    //cout<<vertexNumber<<' '<<edgeNumber<<' '<<costVertexNumber<<'\n';
    //cout<<'\n';
    //cout<<singleServerCost;
    //cout<<'\n';

    //预先为邻接表开辟空间
    for(int i=0; i<vertexNumber; i++){
        V tmp1;
        Table.push_back(tmp1);
        vector <E> tmp2;
        edge.push_back(tmp2);
    }
    //预先为子图开辟空间
    for(int i=0; i<vertexNumber; i++){
        V tmp;
        subTable.push_back(tmp);
    }

    edge = vector<vector<E>>(vertexNumber, vector<E>(vertexNumber));
    //构造邻接表
    int vertex1, vertex2, bandwidth, cost;
    for(int i=0; i<edgeNumber; i++){
        vertex1 = readNumber(p);
        vertex2 = readNumber(p);
        bandwidth = readNumber(p);
        cost = readNumber(p);
        line++;
        p = topo[line];
        //cout<<vertex1<<' '<<vertex2<<' '<<bandwidth<<' '<<cost<<'\n';
        E tmp;
        tmp.setEdge(bandwidth, cost, vertex2);
        edge[vertex1][vertex2] = tmp;
        tmp.setEdge(bandwidth, cost, vertex1);
        edge[vertex2][vertex1] = tmp;

        Table[vertex1].nextVertex.push_back(vertex2);
        Table[vertex2].nextVertex.push_back(vertex1);
    }
    line++;
    p = topo[line];
    //cout<<'\n';

    //记录消费节点信息
    int srcNumber, desNumber, reqBandwidth;
    for(int i=0; i<costVertexNumber; i++){
        srcNumber = readNumber(p);
        desNumber = readNumber(p);
        reqBandwidth = readNumber(p);
        line++;
        p = topo[line];
        //cout<<srcNumber<<' '<<desNumber<<' '<<reqBandwidth<<'\n';
        //对顶点集合(邻接表)进行修改
        Table[desNumber].setClient(reqBandwidth);
        subTable[desNumber].setClient(reqBandwidth,desNumber,0);
        //对特殊定点集合进行修改
        specialNode tmp;
        tmp.sequenceNumber = srcNumber;
        tmp.relevantNumber = desNumber;
        tmp.reqBandwidth = reqBandwidth;
        client.push_back(tmp);
    }

    //计算节点的度
    //calculateDegree();

    //为消费节点建立路由表
    clientPathTable = clientPath();
    //计算中心点和中央点
    calculateCenter1();
    calculateCenter2();
    //生成优先级定点序列
    //Max_T(center1);
    Max_T(center2);
}

void Graph::saveGraph(){
    //邻接矩阵
    int edge_tmp[vertexNumber][vertexNumber];

    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber; j++){
            edge_tmp[i][j] = 0; 
        }
    }
    //构建邻接表
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber; j++){
            int SZ = edge[i].size();
            for(int k=0; k<SZ;k++){
                int index = edge[i][k].dest;
                edge_tmp[i][index] = 1;
                edge_tmp[index][i] = 1;
            }
        }
    }

    //写邻接表
    string str;
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber; j++){
            if(edge_tmp[i][j]>0){
                str += "1 ";
            }else{
                str += "0 ";
            }
        }
        str += '\n';
    }
    char *topo_tmp1 = new char [strlen(str.c_str())+1];
    strcpy(topo_tmp1,str.c_str());
    write_result(topo_tmp1, "graph_edge.txt");
    delete [] topo_tmp1;

    //消费节点 
    
    str = "";
    for(int i=0; i<vertexNumber;i++){
        str += "0 ";
    }


    list<specialNode>::iterator iter1;
    iter1 = client.begin();

    for(; iter1!=client.end(); iter1++){
        int num_tmp = (*iter1).relevantNumber;
        str.replace(2*num_tmp,1,"1");
    }
    char *topo_tmp2 = new char [strlen(str.c_str())+1];
    strcpy(topo_tmp2,str.c_str());
    write_result(topo_tmp2, "graph_client1.txt");


    str = "";
    for(iter1 = client.begin();iter1!=client.end(); iter1++){
        int num_tmp = (*iter1).relevantNumber;
        if(num_tmp>0){
            stack <char> st;    
            while(num_tmp!=0){
                char c = '0' + num_tmp % 10;
                st.push(c);
                num_tmp /= 10;
            }
            while(!st.empty()){
                char c = st.top();
                st.pop();
                string str_tmp(1,c);
                str += str_tmp;
            }
            str += " ";
        }else{
           str += "0 "; 
        }
    }
    char *topo_tmp3 = new char [strlen(str.c_str())+1];
    strcpy(topo_tmp3,str.c_str());
    write_result(topo_tmp3, "graph_client2.txt");
    delete [] topo_tmp2;
}

//从i到j的下一个节点,没有则返回-1
int Graph::nextNode(int i, int center){
    if(clientPathTable.empty())
        return -1;
    else
        return clientPathTable[i].previous[center];
}

//计算"中心点"函数
void Graph::calculateCenter1(){
    int * cost = new int [costVertexNumber] ();//全部初始化为0
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<costVertexNumber; j++){
            cost[i] +=  clientPathTable[j].leastCost[i];
        }
    }
    int minCost = cost[0];
    center1 = 0;
    for(int i=1; i<vertexNumber; i++){
        if(minCost > cost[i]){
            minCost = cost[i];
            center1 = i;
        }
    }
    delete [] cost;
}

//计算中央点函数
void Graph::calculateCenter2(){
    int * cost = new int [costVertexNumber] ();//全部初始化为0
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<costVertexNumber; j++){
            cost[i] +=  clientPathTable[j].leastCost[i] * Table[clientPathTable[j].start].requireBandwidth;
        }
    }
    int minCost = cost[0];
    center2 = 0;
    for(int i=1; i<vertexNumber; i++){
        if(minCost > cost[i]){
            minCost = cost[i];
            center2 = i;
        }
    }
    delete [] cost;
}

//降序排列
bool compare(V v1, V v2){
    return v1.traffic > v2.traffic;
}

void Graph::Max_T(int center){
    //step1:生成树(根据最短路),构建图的时候已经完成
    //step2:初始化t,构造函数中已经完成
    //step3:
    int k1, k2;
    for(int i=0; i<vertexNumber; i++){
        k1 = i;
        subTable[i].traffic += subTable[i].requireBandwidth; 
        do{
            k2 = nextNode(k1, center);
            subTable[k2].traffic += subTable[i].requireBandwidth;
            k1 = k2;
        }while(k2 != center);
    //根据t进行排序
    sort(subTable.begin(),subTable.end(),compare);

    }
}

//生成一条路由,并且保存了路径中的倒数第二个节点
Path Graph::searchPath(int start, int end)
{
    Path path(vertexNumber,MAXCOST,noVertex);
    vector<bool> usedVertex = vector<bool>(vertexNumber, false); //点都没用过

    int present = start;
    path.start = start;
    list<int>::iterator i;

    bool isDone = 0;

    path.leastCost[present] = 0;
    
    while(!isDone)
    {
        //加入一个新节点
        usedVertex[present] = true;
        //加入新节点后更新权重
        for (i = Table[present].nextVertex.begin() ; i != Table[present].nextVertex.end(); ++i) 
        {
            if (edge[present][*i].perCost + path.leastCost[present] < path.leastCost[*i])
            {
                path.leastCost[*i] = edge[present][*i].perCost + path.leastCost[present];
                path.previous[*i] = present;
            }
        }
        //寻找下一个新节点
        present = findNext(usedVertex, path);
        if (present == end)
            isDone = 1;
    }

    return path;
}

vector<Pair> Graph::serverPath()
{
    list<specialNode>::iterator i, j;
    int k = 0;
    Path onePath(vertexNumber, MAXCOST, noVertex);
    vector<Pair> costPair(server.size() * client.size());

    for (i = server.begin(); i != server.end(); ++i)
    {
        //这个函数可以优化,可以在所有client进入路径后,终止函数
        onePath = searchPath((*i).relevantNumber);
        for (j = client.begin(); j != client.end(); ++j)
        {
            costPair[k].server = *i;
            costPair[k].client = *j;
            costPair[k].cost = onePath.leastCost[(*j).relevantNumber];
            costPair[k].previous = onePath.previous;
            ++k;
        }
    }
    return costPair;
}

//生成从消费节点出发的路由表
vector<Path> Graph::clientPath()
{
    list<specialNode>::iterator i;
    int j = 0;
    vector<Path> pathTable(client.size(),{vertexNumber,MAXCOST,noVertex});
    for (i = client.begin(); i != client.end(); ++i)
    {
        //pathTable[j++] = searchPath((*i).relevantNumber, center1);
        pathTable[j++] = searchPath((*i).relevantNumber);
    }
    return pathTable;
}

int Graph::findNext(vector<bool> usedVertex, Path path)
{
    int i = 0, j = -1;
    int tmp = MAXCOST;
    for (i = 0; i < vertexNumber; ++i)
    {
        if (!usedVertex[i] && path.leastCost[i] <= tmp)
        {
            j = i;
            tmp = path.leastCost[i];
        }
    }
    return j;
}





