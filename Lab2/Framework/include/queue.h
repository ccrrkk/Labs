#pragma once

#include "list.h"
#include <stdexcept>

namespace DATA_STRUCTURE {

template<class data_base>
class queue : public list<data_base> {
    public:
        queue() = default;
        ~queue() = default;

        bool empty() override {
            if(top_index!=tail_index) return false;
            return true;
        }
        void pop() override {
            if(!empty()){
                tail_index = (tail_index+1) % MAX_LINK_LIST_NUM;
            } 
            else {
                throw std::out_of_range("the queue is empty!");
            }
        }
        data_base top() override {
            if(!empty()){
                return list_data[tail_index]; // 队列的头部是tail_index指向的元素!!
            }
            throw std::out_of_range("the queue is empty!");
        }
        void push(data_base push_data) override {
            if((top_index+1)%MAX_LINK_LIST_NUM!=tail_index){
                list_data[top_index] = push_data; 
                top_index = (top_index+1)%MAX_LINK_LIST_NUM;            
            }
            else{
                throw std::overflow_error("the queue is full!");
            }
        }
        void clear() override {
            top_index = tail_index = 0;
        }
    private:
        int top_index = 0;
        int tail_index = 0;
        data_base list_data[MAX_LINK_LIST_NUM];
};

}
