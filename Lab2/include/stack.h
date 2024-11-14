#pragma once

#include "list.h"
#include <stdexcept>

namespace DATA_STRUCTURE {

template<class data_base>
class stack : public list<data_base> {
    public:
        stack() = default;
        ~stack() = default;

        bool empty() override {
            if(top_index!=0) return false;
            return true;
        }
        void pop() override {
            if (!empty()) {
                --top_index;
            }
        }
        data_base top() override {
        if (!empty()) {
            data_base temp = list_data[top_index - 1];
            return temp;
        }
        throw std::out_of_range("Stack is empty");  // EMPTY
    }
        void push(data_base push_data) override {
            if (top_index >= MAX_LINK_LIST_NUM) {
                throw std::overflow_error("Stack is full");  // OVERFLOW
            }
            list_data[top_index++] = push_data;
        }
        void clear() override {
            top_index = 0;
        }
    private:
        int top_index = 0;
        data_base list_data[MAX_LINK_LIST_NUM];
};

}
