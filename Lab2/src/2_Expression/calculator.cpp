#include "calculator.h"
#include <cmath> 
#include <stdexcept>
#include <iostream>

namespace DATA_STRUCTURE {

std::string calculator::get_expr() {
    return expr;
}

bool calculator::legal() {
    int bracket = 0;
    bool preOp = true;  //上一个是否为空格或者为符号
    std::string expr = get_expr();
    for(size_t i = 0;i < expr.length();i++){
        char ch = expr[i];
        if(ch==' '||ch=='.') continue;
        else if(ch=='(') {
            bracket++;
            preOp = true;
            if(i!=0&&!preOp) return false;
        }
        else if(ch==')') {
            if(preOp) return false;
            bracket--;
            preOp = false;            
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'){
            if(preOp) return false;
            preOp = true;
        }
        else if(48<=ch&&ch<=57){
            if(i!=0&&expr[i-1]==')') return false;
            preOp = false;
        }
        else{
            return false;
        }
    }
    return bracket==0;
}

int calculator::priority_regular(char c) {
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
int calculator::priority(char c1, char c2) {
    int p1 = priority_regular(c1), p2 = priority_regular(c2);
    if(c1=='('&&c2==')') return 2;
    if(c1=='('&&c2!='#'&&c2!=')') return 0;
    if(c1!='#'&&c1!='('&&c2=='(') return 0; //c2高
    if(c1!='#'&&c1!='('&&c2==')') return 1; //c1高
    if(c1=='('&&c2!='#'&&c2!=')') return 0; //c2高
    if(c1==')'&&c2!='#'&&c2!=')') return 1; //c1高
    if(c1=='('&&c2=='(') return 0;
    if(c1==')'&&c2==')') return 1;
    if(p1>=p2) return 1;
    return 0;
}

struct calculator::element calculator::read_num(int& i) {
    double decimalPlace = 1;//小数办法
    int flag = 0;  // 0 indicates integer, 1 indicates double
    int num_int = 0;
    double num_double = 0;
    std::string expr = get_expr();
    while (i < expr.length() && isspace(expr[i])) {
        i++;
    }
    while (i < expr.length() && isdigit(expr[i])) {
        num_int = num_int * 10 + (expr[i] - '0');
        i++;
    }
    // 如果遇到小数点，继续读取小数部分
    if (i < expr.length() && expr[i] == '.') {
        flag = 1;  // 表示小数
        i++;
        decimalPlace = 0.1;
        while (i < expr.length() && isdigit(expr[i])) {
            num_double += (expr[i] - '0') * decimalPlace;
            decimalPlace *= 0.1;
            i++;
        }
    }
    if (flag == 0) {
        return {flag, num_int, 0};        // 返回整数
    } 
    else {
        return {flag, num_int, num_double}; 
    }
}

struct calculator::element calculator::operate(struct calculator::element element1, char c, struct calculator::element element2) {
    struct calculator::element result;
    
    if(element1.flag == 0 && element2.flag == 0) {
        // 如果两个都是整数
        int num1 = element1.num_int;
        int num2 = element2.num_int;
        
        switch(c) {
            case '+':
                result.num_int = num1 + num2;
                result.flag = 0;
                break;
            case '-':
                result.num_int = num1 - num2;
                result.flag = 0;
                break;
            case '*':
                result.num_int = num1 * num2;
                result.flag = 0;
                break;
            case '/':
                if(num2 != 0) {
                    result.num_int = num1 / num2;
                    result.flag = 0;
                } 
                else {
                    // 处理除以0的情况,自动退出程序
                    std::cout<<"ERROR: Division by zero"<<std::endl;
                    std::exit(1);
                }
                break;
            case '^':
                result.num_int = static_cast<int>(pow(num1, num2));  // 使用pow计算幂
                result.flag = 0;
                break;
            default:
                std::cout<<"ERROR: Unknown operand"<<std::endl;
                std::exit(1);
                break;
        }
    } 
    else {
        // 如果任意一个是浮点数，或者两个都是浮点数
        double num1 = element1.num_int + element1.num_double;
        double num2 = element2.num_int + element2.num_double;

        double temp;
        switch(c) {
            case '+':
                temp = num1 + num2;
                break;
            case '-':
                temp = num1 - num2;
                break;
            case '*':
                temp = num1 * num2;
                break;
            case '/':
                if(num2 != 0.0) {
                    temp = num1 / num2;
                } 
                else {
                    std::cout<<"ERROR: Division by zero"<<std::endl;
                    std::exit(1);
                }
                break;
            case '^':
                temp = pow(num1, num2);  
                break;
            default:
                std::cout<<"ERROR: Unknown operand"<<std::endl;
                std::exit(1);
                break;
        }
        result.num_int = std::floor(temp);
        result.num_double = temp - result.num_int;
        result.flag = 1;
    }

    return result;
}

bool calculator::legal_op(char ch){
    if(ch=='#'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='('||ch==')'){
        return true;
    }
    return false;
}

struct calculator::element calculator::get_ans() {
    int i=0;
    std::string expr = get_expr();
    op.push('#');//开始字符
    while(i!=expr.length()||op.top()!='#'){
        // std::cout<<"i="<<i<<"expr[i]="<<expr[i]<<std::endl;
        element num1, num2, new_num;
        if(i!=expr.length()&&legal_op(expr[i])){
            char top_op = op.top();
            int flag = priority(top_op,expr[i]);
            switch (flag){
                case 0://新的大于旧的
                    op.push(expr[i]);
                    i++;
                    break;
                case 1: //旧的大于新的
                    num1 = num.top();
                    num.pop();                    
                    num2 = num.top();
                    num.pop();
                    new_num = operate(num2,top_op,num1);
                    num.push(new_num);
                    op.pop();
                    break;
                case 2:
                    op.pop(); //删除括号 
                    i++; 
                    break;
            }
        }
        else if(i==expr.length()){
            if(op.top()!='#'){
                auto num1 = num.top();
                num.pop();                    
                auto num2 = num.top();
                num.pop();
                auto new_num = operate(num2,op.top(),num1);
                op.pop();
                num.push(new_num);           
            }
        }
        else if(48<=expr[i]&&expr[i]<=57){//数字
            element n = read_num(i);
            num.push(n);
        }
    }
    return num.top();
}

}