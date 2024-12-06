#include "../include/dijkstra.h"
#include <iostream>
#include <climits>
#include <bits/stdc++.h>
void dijkstra::ssp(int s)
{
    for(int i=0;i<g.vertex_num;i++){
        vertex[i].dist = INT_MAX;
        vertex[i].sure = 0;
        vertex[i].path = -1;
    }
    vertex[s].dist = 0;
    for(int i=0;i<g.vertex_num;i++){
        int u = -1;
        int min_dis = INT_MAX;
        for(int j=0;j<g.vertex_num;j++){
            if(!vertex[j].sure&&vertex[j].dist<min_dis){
                u = j;
                min_dis = vertex[j].dist;
            }
        }
        if(u==-1) break;
        vertex[u].sure = 1;
        graph::Edge* e = g.vertex[u].head;
        while(e){
            int v = e->adj;
            int new_dist = vertex[u].dist + e->weight;

            // 如果通过u到达v的路径更短，更新v的最短路径
            if (new_dist < vertex[v].dist) {
                vertex[v].dist = new_dist;
                vertex[v].path = u;  // 记录前驱顶点
            }
            e = e->next;
        }
    }
    for(int i=0;i<g.vertex_num;i++){
        if(i==s) {
            std::cout<<i<<":"<<std::endl;
            continue;
        }
        std::cout<<i<<":"<<vertex[i].dist<<" ";
        print(i);
        std::cout<<std::endl;
    }

}
void dijkstra::print(int u)
{
    if (vertex[u].path == -1) {
        std::cout << u << " ";
        return;
    }
    print(vertex[u].path);
    std::cout << u << " ";
}