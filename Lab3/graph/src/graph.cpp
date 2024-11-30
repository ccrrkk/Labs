#include "../include/graph.h"
#include<iostream>


void graph::init(int u[],int v[],int w[])
{
    for(int i=0;i<edge_num;i++){
        struct Edge* node = new Edge;
        node->adj = v[i];
        node->weight = w[i];
        node->next = vertex[u[i]].head;
        vertex[u[i]].head = node;
        struct Edge* nodej = new Edge;
        nodej->adj = u[i];
        nodej->weight = w[i];
        nodej->next = vertex[v[i]].head;
        vertex[v[i]].head = nodej;
    }
}
void graph::dfs(int s) {
    vertex[s].visited = 1;
    std::cout << s << std::endl; 

    struct Edge* p = vertex[s].head;
    while (p) {
        if (!vertex[p->adj].visited) {
            dfs(p->adj);
        }
        p = p->next;
    }
}