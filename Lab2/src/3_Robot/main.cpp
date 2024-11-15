#include "walk.h"

int main() {
    // int steps = 6;
    // int n = 3;
    // int gold[1001] = {1, 2, 
    //                 3, 3, 
    //                 5, 0
    //                 }; //相当于二维数组压缩到了一维：(1,2),(3,3),...
    // int value[501] = {5, 2, 4};
    int steps,n;
    int value[501];
    int gold[1001];
    while(1){
        std::cin >> steps >> n;
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", gold + 2 * i, gold + 2 * i + 1, value + i);
        DATA_STRUCTURE::walk p(steps, n, gold, value);
        // p.print_para();
        std::cout << p.get_value() << std::endl;     
    }
    return 0;
}
