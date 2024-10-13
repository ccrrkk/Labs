#include "../include/Game.h"

Game::Game() = default;

void Game::initGame() {
    gameBoard.reset();
    score = 0;
    moveCount = 0;
    historyGameBoards = std::stack<GameBoard>();
    historyScore = std::stack<int>(); //补写historyScore记录历史分数
    startTime = std::chrono::system_clock::now();
    historyGameBoards.push(gameBoard);  // Save initial state
    historyScore.push(score);
}

void Game::updateGame(Direction direction) {

    // Get move score and update score
    score += gameBoard.move(direction);
    // update move count
    moveCount++;
    historyGameBoards.push(gameBoard);
    historyScore.push(score);

}

void Game::undoLastMove() {
    if (historyGameBoards.size() > 1) {
        // Remove current state
        historyGameBoards.pop();
        // Restore previous state
        gameBoard = historyGameBoards.top();
        // Remove current state
        historyScore.pop();
        // Restore previous state
        score = historyScore.top();
        moveCount--;

    } else {
        gameBoard.reset();
        score = 0;
        moveCount = 0;
    }
}

bool Game::hasWon() const {
    return gameBoard.hasWinningTile();
}

bool Game::hasLost() const {
    return gameBoard.isGameOver();
}

double Game::getElapsedTime() const {
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

int Game::getScore() const {
    return score;
}

int Game::getMoveCount() const {
    return moveCount;
}

const GameBoard& Game::getGameBoard() const {
    return gameBoard;
}