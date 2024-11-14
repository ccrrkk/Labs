#include <iostream>
#include <stdexcept>
#include <cstdlib>  // 引入 exit()

int priority_regular(char c) {
    switch(c) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        case ')': return 4;
        case '#': return -1;  // 假设#是栈底符号
        default: return -1; // 非法字符
    }
}

// 比较两个运算符的优先级，返回1表示c1优先级高，0：c2，2：相等
int priority(char c1, char c2) {
    int p1 = priority_regular(c1), p2 = priority_regular(c2);
    
    // (和)之间的要有特殊优先级处理！！
    if(c1 == '(' && c2 == ')') return 2;
    if(c1 == ')' && c2 == '(') return 2;
    
    if(p1 > p2) return 1; 
    if(p1 < p2) return 0;  
    return 2;  
}

int main(){
    
}