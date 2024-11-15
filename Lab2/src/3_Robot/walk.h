#include <iostream>
#include <math.h>
#include <vector>

#include "queue.h"
#include "unordered_set.h"

namespace DATA_STRUCTURE {

class walk {
    public:
        struct coin{
            int no;
            int x;
            int y;
            int value;
        };
        walk() = default;
        walk(int _steps, int _gold_num, int* _gold, int* _gold_value) {
            steps = _steps;
            gold_num = _gold_num;
            gold = _gold;
            gold_value = _gold_value;
        }
        ~walk() = default;

        void print_para();
        void print_map();
        int get_value();
        std::vector<struct coin> creatmap();
        std::vector<struct coin> coin_map;
    private:
        int gold_num = 0;
        int* gold;
        int* gold_value;
        int steps = 0;

        struct element {
            int steps;
            int value;
            int x, y;
            unordered_set<int> get_gold;
        };
        queue<struct element> q;

        int compute_distance(int i, int x, int y);
};

}