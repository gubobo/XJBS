#-*- coding:utf8 -*-

import networkx as nx                   #导入NetworkX包，为了少打几个字母，将其重命名为nx
import matplotlib.pyplot as plt         #导入绘图包matplotlib
import pdb


file_read = open('tt.txt', 'r')
file_color = open('c.txt', 'r')
try:
    #读入二维邻接矩阵
    matrix = [0 for y in range(100)]   #8*8的零矩阵
    i = 0
    for line in file_read:             #读入每一行
         matrix[i] = line.split(' ')   #将每一行按空格分割
         i = i + 1

    pdb.set_trace()
    #创建图   
    G = nx.Graph()                     #建立一个空的无向图
    v = range(0, i)                    #一维行向量，从1到8递增
    G.add_nodes_from(v)                #从v中添加结点，相当于顶点编号为1到8
    line = file_color.read()           #读取颜色向量
    colors = (line.split(' '))         #颜色向量
    for i in range(len(colors)):
         colors[i] = int(colors[i])    #将字符转为数字
    for x in range(0, len(matrix[0]) - 1):    #添加边
         for y in range(0, len(matrix[0]) - 1):
              if matrix[x][y] == '1':
                   G.add_edge(x, y)


    #绘制网络图G，带标签，           用指定颜色给结点上色
    nx.draw(G, with_labels=True, node_color=colors)  
    plt.show()                       #输出方式: 在窗口中显示这幅图像
finally:
     file_read.close()

