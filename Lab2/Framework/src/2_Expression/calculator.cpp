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
    if(c=='+'||c=='-'){
        return 1;
    }
    else if(c=='*'||c=='/'){
        return 2;
    }
    else if(c=='^'){
        return 3;
    }
    else if(c=='('){
        return 4;
    }
    else if(c==')'){
        return 0;
    }
    return -1;
}

int calculator::priority(char c1, char c2) { //比较c1和c2哪个大,c1较大返回1
    int pc1 = priority_regular(c1),pc2= priority_regular(c2);
    if(c1=='('&&c2==')') return 2;//相等返回2
    if(pc1>=pc2) return 1;//c1>c2返回1
    return 0;//c1<c2返回0
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
    } else {
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
                result.num_double = pow(num1, num2);  
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
    while(i!=expr.length()){
        //现在思路：左括号直接往里面放（反正无论如何左括号都不可能有弹出）,其余按照大小比较  我的运算规则给做括号至高无上的权利，好像无所谓
        //右括号的优先级要降低！！！
        if(legal_op(expr[i])){
            char top_op = op.top();
            int flag = priority(top_op,expr[i]);
            switch (flag){
                case 0://新的大于旧的
                    op.push(expr[i]);
                    i++;
                    break;
                case 1: //旧的大于新的
                    auto num1 = num.top();
                    num.pop();                    
                    auto num2 = num.top();
                    num.pop();
                    auto new_num = operate(num2,expr[i],num1);
                    num.push(new_num);
                    break;
                case 2:
                    op.pop(); //删除括号 
                    i++; 
                    break;
            }
        }
        else if(48<=expr[i]&&expr[i]<=57){//数字
            element n = read_num(i);
            num.push(n);
        }
    }
    return {0, 0, 0};
}
