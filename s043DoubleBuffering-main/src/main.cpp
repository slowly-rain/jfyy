#include "common.h"

// Forward declarations
void initConsoleBuffers();
void restoreDefaultBuffer();
void showMenuScreen();
void showPlayingScreen(bool paused);
void showGameOverScreen();
void processInput();
void updateLogic();
void updateBombs();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleA("Console Double Buffering Snake");
    resetGame();
    showMenuScreen();
    while (gameState != GameState::EXIT) {
        if (gameState == GameState::MENU) { processInput(); Sleep(50); continue; }
        if (gameState == GameState::RUNNING) { showPlayingScreen(false); processInput(); updateLogic(); updateBombs(); Sleep(speed); continue; }
        if (gameState == GameState::PAUSED) { showPlayingScreen(true); processInput(); Sleep(50); continue; }
        if (gameState == GameState::GAME_OVER) { showGameOverScreen(); processInput(); Sleep(100); continue; }
    }
    restoreDefaultBuffer();
    cout << "\nThanks for playing!\n";
    return 0;
}