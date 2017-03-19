#include "graph.h"
#include "lib_io.h"

#include <string>
#include <cstring>
#include <stack>
#include <iostream>
using std::string;
using std::stack;
using std::cout;

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
        degree1[i] = Table[i].Edge.size();
        for(int j=0; j<degree1[i]; j++){
            degree2[i] += Table[i].Edge[j].totalBandwidth;
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
        V tmp;
        Table.push_back(tmp);
    }

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
        Table[vertex1].addEdge(tmp);
        tmp.setEdge(bandwidth, cost, vertex1);
        Table[vertex2].addEdge(tmp);
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
        //对特殊定点集合进行修改
        specialNode tmp;
        tmp.squenceNumber = srcNumber;
        tmp.relevantNumber = desNumber;
        tmp.reqBandwidth = reqBandwidth;
        client.push_back(tmp);
    }

    //计算节点的度
    //calculateDegree();

    //预先为子图开辟空间
    for(int i=0; i<vertexNumber; i++){
        V tmp;
        subTable.push_back(tmp);
    }
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
            int SZ = Table[i].Edge.size();
            for(int k=0; k<SZ;k++){
                int index = Table[i].Edge[k].dest;
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
    for(int i=0; i<costVertexNumber; i++){
        int num_tmp = client[i].relevantNumber;
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
    char *topo_tmp2 = new char [strlen(str.c_str())+1];
    strcpy(topo_tmp2,str.c_str());
    write_result(topo_tmp2, "graph_client.txt");
    delete [] topo_tmp2;
}



/*
//邻接矩阵表示情况下的建图函数
void Graph::calculateDegree(){
    degree1 = new int [vertexNumber];
    degree2 = new int [vertexNumber];
    for(int i=0; i<vertexNumber; i++){
        degree1[i] = 0;
        degree2[i] = 0;
    }
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber; j++){
            degree1[i] += ((Edge[i][j].totalBandwith>0) ? 1:0);
            degree2[i] += Edge[i][j].totalBandwith;
        }
    }
}

void Graph::creatGraph(char *　topo){
    char * p = topo;
    vertexNumber = readNumber(p);//网络节点数目
    edgeNumber　＝　readNumber(p);//网络链路数目
    costVertexNumber = readNumber(p);//消费节点数目
    p++;//跳过一个换行
    singleServerCost = readNumber(p);//视频内容服务器部署成本
    p++;//跳过一个换行
    
    //申请内存
    //度
    degree = new int [vertexNumber];
    for(int i=0; i<vertexNumber; i++){
        degree[i] = 0;
    }
    //邻接矩阵
    Edge = (E **) new E *[vertexNumber];
    for(int i=0; i<vertexNumber; i++){
        Edge[i] = new E [vertexNumber];
    }
    //顶点
    Vertex = new V [vertexNumber];
    client = new specialNode [vertexNumber];
    server = new specialNode [vertexNumber];

    //构造邻接矩阵
    int vertex1, vertex2, bandwidth, cost;
    for(int i=0; i<edgeNumber; i++){
        vertex1 = readNumber(p);
        vertex2 = readNumber(p);
        bandwidth = readNumber(p);
        cost = readNumber(p);
        Edge[vertex1][vertex2].setEdge(bandwidth, cost);
        Edge[vertex2][vertex1].setEdge(bandwidth, cost); 
    }
    p++;//跳过一个换行

    //记录消费节点
    int srcNumber, desNumber, reqBandwidth;
    for(int i=0; i<costNodeNum; i++){
        srcNumber = readNumber(p);
        desNumber = readNumber(p);
        reqBandwidth = readNumber(p);
        Vertex[i].setClient(reqBandwidth);//顶点集设置
        
        client.squenceNumber = srcNumber;
        client.relevantNumber = desNumber;
    }
    //计算节点的度
    //calculateDegree();

    //子图的邻接矩阵
    subGraph = (int **) new int * [vertexNumber];
    for(int i=0; i<vertexNumber; i++){
        subGraph[i] = new int [vertexNumber];
    }
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber; j++){
            subGraph[i][j] = 0;
        }
    }
} 

void Graph::saveGraph(){
    //邻接矩阵
    string str;
    for(int i=0; i<vertexNumber; i++){
        for(int j=0; j<vertexNumber-1; j++){
            if(Edge[i][j].totalBandwith>0){
                str += "1 ";
            }else{
                str += "0 ";
            }
        }
        if(Edge[i][vertexNumber-1].totalBandwith>0){
            str += "1\n";
        }else{
            str += "0\n";
        }
    }
    char *topo_tmp = str.c_str();
    write_result(topo_tmp, "graph_edge.txt");
    //消费节点
    str = "";
    for(int i=0; i<costVertexNumber; i++){
        int num_tmp = client.relevantNumber;
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
                str += " ";
            }
        }else{
           str += "0 "; 
        }
    }
    topo_tmp = str.c_str();
    write_result(topo_tmp, "graph_client.txt");
}
*/

