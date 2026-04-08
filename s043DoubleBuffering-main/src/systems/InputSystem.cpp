#include "../common.h"

void processInput() {
    if (!_kbhit()) return;
    int ch = _getch();
    int key = -1;
    bool special = (ch == 0 || ch == 224);
    if (special) key = _getch();
    auto applyDir = [&](eDirection newDir) { if (dir == eDirection::STOP || !isOpposite(dir, newDir)) dir = newDir; };
    
    // MENU 状态
    if (gameState == GameState::MENU) {
        if (ch == 'n' || ch == 'N') { resetGame(); gameState = GameState::RUNNING; initConsoleBuffers(); return; }
        if (ch == 'l' || ch == 'L') {
            if (loadGame("savegame.json")) {
                gameState = GameState::RUNNING;
                initConsoleBuffers();
            } else {
                restoreDefaultBuffer();
                cout << "Load failed. 按任意键继续...";
                _getch();
                showMenuScreen();
            }
            return;
        }
        if (ch == 'q' || ch == 'Q') { gameState = GameState::EXIT; return; }
    } 
    // RUNNING 状态：允许移动、暂停、保存
    else if (gameState == GameState::RUNNING) {
        // 空格键暂停
        if (ch == ' ') { gameState = GameState::PAUSED; return; }
        
        // 方向键处理（仅在RUNNING状态允许）
        if (special) {
            if (key == 75) applyDir(eDirection::LEFT);
            if (key == 77) applyDir(eDirection::RIGHT);
            if (key == 72) applyDir(eDirection::UP);
            if (key == 80) applyDir(eDirection::DOWN);
            return;
        }
        if (ch == 'a' || ch == 'A') applyDir(eDirection::LEFT);
        if (ch == 'd' || ch == 'D') applyDir(eDirection::RIGHT);
        if (ch == 'w' || ch == 'W') applyDir(eDirection::UP);
        if (ch == 's' || ch == 'S') applyDir(eDirection::DOWN);
        
        // 其他功能键
        if (ch == 'z' || ch == 'Z') { saveGame("savegame.json"); return; }
        if (ch == 'q' || ch == 'Q') { gameState = GameState::EXIT; return; }
    } 
    // PAUSED 状态：不允许移动，只允许继续、保存、退出
    else if (gameState == GameState::PAUSED) {
        // 任意键都可以继续游戏（但Z和Q除外）
        if (ch == 'z' || ch == 'Z') { saveGame("savegame.json"); return; }
        if (ch == 'm' || ch == 'M') { gameState = GameState::MENU; restoreDefaultBuffer(); showMenuScreen(); return; }
        if (ch == 'q' || ch == 'Q') { gameState = GameState::EXIT; return; }
        // 其他任意键继续游戏
        gameState = GameState::RUNNING;
        return;
    } 
    // GAME_OVER 状态
    else if (gameState == GameState::GAME_OVER) {
        if (ch == 'r' || ch == 'R') { resetGame(); gameState = GameState::RUNNING; initConsoleBuffers(); return; }
        if (ch == 'm' || ch == 'M') { gameState = GameState::MENU; restoreDefaultBuffer(); showMenuScreen(); return; }
        if (ch == 'q' || ch == 'Q') { gameState = GameState::EXIT; return; }
        if (ch == 'z' || ch == 'Z') { saveGame("savegame.json"); return; }
    }
}