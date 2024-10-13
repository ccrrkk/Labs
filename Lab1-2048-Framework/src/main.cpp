#include <iostream>
#include <fstream> // ���� fstream ͷ�ļ�
#include "../include/Game.h"
#include "../include/GameRender.h"
#include "../include/InputHandler.h"

int main(){ 
    Game game; 
    // Display welcome message 
    TerminalRender::displayWelcomeMessage(); // Wait for the start game command 
    InputType command; 
    while (true) { 
        command = InputHandler::handleInput(); 
        if (command == InputType::START_GAME) { 
            break; 
        }
        else{ 
            std::cout << "Invalid input. Press 'E' to start the game.\n"; 
        } 
    } 
    // Initialize the game 
    game.initGame(); 
    TerminalRender::render(game.getGameBoard(), game.getScore(), game.getMoveCount()); 
    // Game loop 
    while (true) { 
        // Handle user input 
        InputType input = InputHandler::handleInput(); 
        if (input == InputType::UNDO) { 
            // Implement undo functionality
            game.undoLastMove();
        }
        else if (input == InputType::QUIT_GAME) { 
            // Think about how to handle quitting the game 
            return 0;
        } 
        else { 
            Direction direction; 
            switch (input) { 
                case InputType::UP: 
                    direction = Direction::UP; 
                    break; 
                case InputType::DOWN: 
                    direction = Direction::DOWN; 
                    break; 
                case InputType::LEFT: 
                    direction = Direction::LEFT; 
                    break; 
                case InputType::RIGHT: 
                    direction = Direction::RIGHT; 
                    break; 
                default: 
                    std::cout << "Invalid input. Use arrow keys to move, U to undo, or Q to quit.\n"; 
                    continue;
            } 
                // Update the game state 
            game.updateGame(direction);
        } 
            // Render the updated game board 
            // refer to how the game is initially rendered 
        TerminalRender::clearScreen();
        TerminalRender::render(game.getGameBoard(), game.getScore(), game.getMoveCount());

            // Check for win or lose conditions 
        if (game.hasWon()) { 
            TerminalRender::displayWinMessage(); 
            //������С����
            std::ifstream inFile("D:/Data Structure/Experiments_DataStructure/Lab1-2048-Framework/src/history.txt"); // ���ļ��Զ�ȡ
            int historyNumber;

            // ����ļ��Ƿ�ɹ��򿪲���ȡ����
            if (inFile.is_open()) {
                inFile >> historyNumber; // ��ȡ�ļ��е�����
                inFile.close(); // �ر��ļ�
            } else {
                std::cerr << "Unable to open history.txt for reading!" << std::endl;
                return 1; // ���ش�����
            }
            // �Ƚ�moveCount��historyNumber
            int moveCount = game.getMoveCount();
            if (moveCount < historyNumber) {
                std::ofstream outFile("D:/Data Structure/Experiments_DataStructures/Lab1-2048-Framework/src/history.txt"); // ���ļ���д��
                if (outFile.is_open()) {
                    outFile << moveCount; // ����д���µ�����
                    outFile.close(); // �ر��ļ�
                    std::cout << "Updated historical best record: " << moveCount << std::endl;
                } 
                else {
                    std::cerr << "Unable to open history.txt for writing!" << std::endl;
                    return 1; // ���ش�����
                }
            }
            break; 
        } 
        else if (game.hasLost()) { 
            TerminalRender::displayLoseMessage(); 
            break; 
        } 
    } 
    // Display elapsed time 
    TerminalRender::displayElapsedTime(game.getElapsedTime());
    while (true) {
        if (InputHandler::handleInput() == InputType::QUIT_GAME) {
            break;
        }
    }
    return 0; 
}