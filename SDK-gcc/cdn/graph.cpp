#include "graph.h"
#include "lib_io.h"

#include <string>
#include <stack>
using std::string;

Graph::~Graph(){
    for(int i=0; i<vertexNumber; i++){
        delete [] Edge[i];
    }
    delete [] Vertex;
}

int Graph::readNumber(char * str){
    int number = 0;
    while((*str)>='0' && (*str)<='9'){
        number = number * 10;
        number = *str - '0';
        str++;
    }
    //只跳过一个特殊符号
    if((*str)=='\n'||(*str)==' '){
        str++;
    }
    return number;
}

void Graph::calculatedegree(){
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
    //calculatedegree();

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

//计算中央点函数
int Graph::calculateCenter2(){

}

