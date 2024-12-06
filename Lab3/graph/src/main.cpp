#include "../include/dijkstra.h"
#include <iostream>


void printgraph(graph g){
    for(int i=0;i<g.vertex_num;i++){
        std::cout << i << "  list:";
        auto p = g.vertex[i].head;
        while(p){            
            std::cout<<"  adj:"<<p->adj<<"  weight:"<<p->weight;
            p = p->next;
        }
        std::cout<<std::endl;
    }
}

int main()
{
    
int n = 10;
int m = 15;
int s = 2;
int u[M] = {1,0,2,5,5,6,2,2,8,6,9,9,3,4,3};
int v[M] = {7,9,4,1,2,1,3,1,5,1,2,5,1,1,8};
int w[M] = {50,50,60,80,80,50,30,70,80,90,80,50,30,20,80};

    //std::cin>>n>>m>>s;
    //for(int i=0;i<m;i++)
        //std::cin>>u[i]>>v[i]>>w[i];

    std::cout << "--------------------------" << std::endl;
    std::cout << "travelsal" << std::endl;
    std::cout << "--------------------------" << std::endl;
    graph g(n, m);
    g.init(u, v, w);
    // std::cout<<"create successfully!"<<std::endl;
    // printgraph(g);
    g.dfs(s);
    std::cout << std::endl << std::endl;

    dijkstra dij(g);
    std::cout <<"--------------------------" << std::endl;
    std::cout << "dijkstra" << std::endl;
    std::cout << "--------------------------" << std::endl;
    dij.ssp(s);
}