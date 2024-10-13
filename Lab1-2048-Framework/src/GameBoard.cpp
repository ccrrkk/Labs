#include "../include/GameBoard.h"
#include <algorithm>
#include <random>
#include <chrono>

GameBoard::GameBoard() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::mt19937(seed);
    reset();
}


void GameBoard::reset() {
    // Initialize the board to be 4x4 with all values set to 0
    board = Board(4, std::vector<int>(4, 0));
    std::uniform_int_distribution<int> dist(0, 3);  // [0, 3] uniform distribution
    std::uniform_int_distribution<int> value_dist(0, 1);

    // Add two initial tiles
    for (int i = 0; i < 2; ++i) {
        int x = dist(generator);
        int y = dist(generator);
        while (board[x][y] != 0) { // Ensure we don't place a tile on an occupied cell
            x = dist(generator);
            y = dist(generator);
        }
        board[x][y] = (value_dist(generator) + 1) * 2; // Place either a 2 or a 4
    }
}


int GameBoard::move(Direction direction) {
    GameBoard::slide(direction);
    int score = GameBoard::merge(direction);
    GameBoard::slide(direction);

    // 放置新的方块：
    std::vector<std::pair<int, int>> space;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                space.emplace_back(i, j);
            }
        }
    }

    if (!space.empty()) {
        std::uniform_int_distribution<size_t> coord_dist(0, space.size() - 1);
        auto random_coord = space[coord_dist(generator)];

        std::uniform_real_distribution<float> float_dist(0.0f, 1.0f);
        float random_float = float_dist(generator);

        int row = random_coord.first;
        int col = random_coord.second;

        board[row][col] = random_float>0.8?4:2;

    } else {
        return -1; 
    }

    return score;
}

//slide和merge已经完成测试

void GameBoard::slide(Direction direction) {
    switch (direction) {
        //个人感觉此处助教代码方向逻辑有误,已修改（原代码去看文档）
        //修正：助教没问题，我和他的（0，0）设置不一样（乐）
        case Direction::DOWN:
            for (int col = 0; col < 4; ++col) {
                int target = 3;
                for (int row = 3; row >= 0; --row) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col],board[row][col]);
                        if (target != row) board[row][col] = 0;
                        --target;
                        }
                    }
            }
            break;
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                int target = 0;
                for (int row = 0; row < 4; row++) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col],board[row][col]);
                        if (target != row) board[row][col] = 0;
                        target++;
                        }
                    }
            }
            break;
        case Direction::LEFT:
            for (int row = 0; row < 4; row++) {
                int target = 0;
                for (int col = 0; col < 4; col++) {
                    if (board[row][col] != 0) {
                        std::swap(board[row][target],board[row][col]);
                        if (target != col) board[row][col] = 0;
                        target++;
                        }
                    }
            }
            break;
        case Direction::RIGHT:
            for (int row = 0; row < 4; row++) {
                int target = 3;
                for (int col = 3; col >= 0; col--) {
                    if (board[row][col] != 0) {
                        std::swap(board[row][target],board[row][col]);
                        if (target != col) board[row][col] = 0;
                        target--;
                        }
                    }
            }
            break;
    }
}

int GameBoard::merge(Direction direction) {
    int moveScore = 0;
    switch (direction) {//先注释掉加分！！！
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                for (int row = 0; row < 3; row++) {
                    if (board[row][col] != 0 && board[row][col] == board[row + 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row + 1][col] = 0;
                    }
                }
            }
            break;

        case Direction::DOWN:
            for (int col = 0; col < 4; ++col) {
                for (int row = 3; row > 0; row--) {
                    if (board[row][col] != 0 && board[row][col] == board[row - 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row - 1][col] = 0;
                    }
                }
            }
            break;

        case Direction::LEFT:
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 3 ; col++) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col + 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col+1] = 0;
                    }
                }
            }
            break;

        case Direction::RIGHT:
            for (int row = 0; row < 4; ++row) {
                for (int col = 3; col > 0; col--) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col - 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col-1] = 0;
                    }
                }
            }
            break;
    }

    return moveScore;
}

bool GameBoard::isGameOver() const {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0) return false;
        }
    }
    return true;
}

bool GameBoard::hasWinningTile() const {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==2048) return true;
        }
    }
    return false;
}

const Board &GameBoard::getBoard() const {
    return board;
}

/*
_______________#########_______________________ 
______________############_____________________ 
______________#############____________________ 
_____________##__###########___________________ 
____________###__######_#####__________________ 
____________###_#######___####_________________ 
___________###__##########_####________________ 
__________####__###########_####_______________ 
________#####___###########__#####_____________ 
_______######___###_########___#####___________ 
_______#####___###___########___######_________ 
______######___###__###########___######_______ 
_____######___####_##############__######______ 
____#######__#####################_#######_____ 
____#######__##############################____ 
___#######__######_#################_#######___ 
___#######__######_######_#########___######___ 
___#######____##__######___######_____######___ 
___#######________######____#####_____#####____ 
____######________#####_____#####_____####_____ 
_____#####________####______#####_____###______ 
______#####______;###________###______#________ 
________##_______####________####______________ 
*/