#include <iostream>
#include <cstdlib>

#include "calculator.h"

int main() {
    DATA_STRUCTURE::calculator a;
    if (a.legal()) {
        std::cout << a.get_expr() << " = ";
        struct DATA_STRUCTURE::calculator::element tmp = a.get_ans();
        if (tmp.flag == 0)
            std::cout << tmp.num_int << std::endl;
        else
            std::cout << tmp.num_int+tmp.num_double << std::endl;
    }
    else{
        std::cout<<"Error: Unvalid expression"<<std::endl;
        exit(1);
    }
    
    DATA_STRUCTURE::calculator b("10*3.2+2*(2+3/2)");
    if (b.legal()) {
        std::cout << b.get_expr() << " = ";
        struct DATA_STRUCTURE::calculator::element tmp = b.get_ans();
        if (tmp.flag == 0)
            std::cout << tmp.num_int << std::endl;
        else
            std::cout << tmp.num_int+tmp.num_double << std::endl;
    }
    else{
        std::cout<<"Error: Unvalid expression"<<std::endl;
        exit(1);
    }

    while (1) {
        std::string s;
        std::cin >> s;
        if (s[0] == 'q')
            break;
        DATA_STRUCTURE::calculator b(s);
        if (b.legal()) {
            std::cout << b.get_expr() << " = ";
            struct DATA_STRUCTURE::calculator::element tmp = b.get_ans();
            if (tmp.flag == 0)
                std::cout << tmp.num_int << std::endl;
            else
                std::cout << tmp.num_int+tmp.num_double << std::endl;
        }
        else{
            std::cout<<"Error: Unvalid expression"<<std::endl;
            exit(1);
        }
    }
    return 0;
}
