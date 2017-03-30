#include "deploy.h"
#include "graph.h"
#include "CostFlow.h"
#include "Genetic.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using std::cout;
using std::ofstream;

//寻找最小费用流的节点数和初始节点位置
//返回最佳的服务器节点数目
int findServer(Graph graph){
    int rankNumber = 25;//人为修改
    int clientNumber = graph.vertexNumber;
    int step = clientNumber / rankNumber + 1;

    int k = clientNumber;//将0-k个节点作为服务器的初始节点
    long long cost = graph.MAXCOST;
    CostFlow cf;
    for(int i=0; i<clientNumber; i=i+step){
        graph.clearServer();
        graph.setServer(i);
        Solution s = cf.FindPath(graph);
        if(s.isWork && cost>s.totalCost){
            cost = s.totalCost;
            k = i;
        }
    }
    //之后几个节点
    for(int i=k+1; i<k+step && i<clientNumber; i++){
        graph.clearServer();
        graph.setServer(i);
        Solution s = cf.FindPath(graph);
        if(s.isWork && cost>s.totalCost){
            cost = s.totalCost;
            k = i;
        }
    }
    //之前几个节点
    for(int i=k-1; i>k-step && i>=0; i--){
        graph.clearServer();
        graph.setServer(i);
        Solution s = cf.FindPath(graph);
        if(s.isWork && cost>s.totalCost){
            cost = s.totalCost;
            k = i;
        }
    }
    return k;
}


//You need to complete the function 
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
    //initialization
    Graph G;
    G.creatGraph(topo);

//    G.saveGraph();

    //test
//    G.searchPath(1);

    specialNode sn;
    vector<int> ser = {37, 13, 15, 38, 34};
    for (int i = 0; i < ser.size(); ++i)
    {
        sn.relevantNumber = ser[i];
        G.server.push_back(sn);
    }
//    G.server = G.client;

    CostFlow tmp;
    Solution result = tmp.FindPath(G);
//    cout<<'\n';
//    cout<<topo[1][MAX_EDGE_NUM-1];


//    char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";
    
//    write_result(topo_file, filename);

    list<stack<int>>::iterator iter;

    ofstream ofile;
    ofile.open("result.txt");
    ofile << result.pathNumber << "\n\n";
    for (iter = result.path.begin(); iter != result.path.end(); ++iter)
    {
        if(!(*iter).empty())
        {
            ofile << (*iter).top();
            (*iter).pop();
        }
        while (!(*iter).empty())
        {
            ofile << ' ' << (*iter).top();
            (*iter).pop();
        }
        ofile << '\n';
    }
    ofile.close();

}
