#include "walk.h"
#include <cmath>

namespace DATA_STRUCTURE {

void walk::print_para() {
    std::cout << steps << std::endl;
    for (int i = 0; i < gold_num; i++) {
        std::cout << *(gold + 2 * i) << " " << *(gold + 2 * i + 1) << " " << *(gold_value + i) << std::endl;
    }
}


void walk::print_map(){
    for(auto i:coin_map){
        std::cout << "No: " << i.no << " Value: " << i.value << " X: " << i.x << " Y: " << i.y << std::endl;
    }
}

std::vector<walk::coin> walk::creatmap() {
    for(int i=0;i<gold_num;i++){
        struct coin temp;
        temp.no = i;//金币编号
        temp.value = *(gold_value+i);
        temp.x = *(gold + 2 * i);
        temp.y = *(gold + 2 * i + 1);
        int flag=1;
        for(auto& c:coin_map){
            if(c.x==temp.x&&c.y==temp.y){
                c.value+=temp.value;
                flag = 0;
                break;
            }
        }
        if(flag){
            coin_map.push_back(temp);
        }
    }
    return coin_map;
}

int walk::compute_distance(int i, int x, int y) {
    int x1 = *(gold+2*i),y1 = *(gold+2*i+1);
    int dx = std::abs(x-x1), dy = std::abs(y-y1);
    int x_num = (dx+1)/2, y_num = (dy+1)/2;
    return x_num+y_num;
}

int walk::get_value() {
    coin_map = creatmap();
    // print_map();
    int max_value = 0;
    element start;
    q.push({0,0,0,0,{}});//START
    int size=1,i=0;
    while(size>0&&i<=gold_num){ //防止都可以拿到，出现死循环
        int temp_size = size;
        for(int j=0;j<temp_size;j++){
            auto move = q.top();
            q.pop();
            size--;
            // std::cout<<move.x<<move.y<<move.value<<std::endl;
            for(auto c:coin_map){
                auto new_move = move;    
                // std::cout<<compute_distance(c.no,move.x,move.y)<<std::endl;        
                if(new_move.steps+compute_distance(c.no,move.x,move.y)<=steps&&!new_move.get_gold.find(c.no)) { //如果下一个金币可达,且没访问过就加入
                    new_move.steps+=compute_distance(c.no,move.x,move.y);
                    new_move.get_gold.insert(c.no);
                    new_move.value+=c.value;
                    new_move.x = c.x;
                    new_move.y = c.y;
                    q.push(new_move);
                    size++;
                }
                else{
                    max_value = std::max(max_value,new_move.value);
                }
            }
        }
        i++;
    }
    for(int i=0;i<size;i++){
        auto temp = q.top();
        q.pop();
        max_value = std::max(max_value,temp.value);
    }

    return max_value;
}

}