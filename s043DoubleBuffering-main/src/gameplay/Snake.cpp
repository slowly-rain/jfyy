#include "../common.h"

void updateLogic() {
    if (dir == eDirection::STOP) return;
    int prevX = tailX[0];
    int prevY = tailY[0];
    if (nTail > 0) {
        tailX[0] = headX;
        tailY[0] = headY;
        for (int i = 1; i < nTail; i++) {
            int prev2X = tailX[i];
            int prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }
    switch (dir) {
        case eDirection::LEFT: headX--; break;
        case eDirection::RIGHT: headX++; break;
        case eDirection::UP: headY--; break;
        case eDirection::DOWN: headY++; break;
        default: break;
    }
    if (headX <= 0 || headX >= mWidth - 1 || headY <= 0 || headY >= mHeight - 1) { gameState = GameState::GAME_OVER; return; }
    for (int i = 0; i < nTail; i++) if (tailX[i] == headX && tailY[i] == headY) { gameState = GameState::GAME_OVER; return; }
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        if (nTail < MAX_TAIL) nTail++;
        spawnFruit();
        // 调整难度
        difficulty = score / 100 + 1;
        // 动态加速：每增加10分，速度加快5毫秒（最低50毫秒）
        speed = 100 - (score / 10) * 5;
        if (speed < 50) speed = 50;
        // 生成炸弹
        int targetBombs = difficulty;
        while (numBombs < targetBombs) {
            spawnBomb();
        }
    }
    // 检查吃到炸弹
    for (int i = 0; i < numBombs; i++) {
        if (headX == bombs[i].x && headY == bombs[i].y) {
            // 吃到炸弹，减少长度
            nTail -= 2;
            // 移除炸弹
            for (int j = i; j < numBombs - 1; j++) {
                bombs[j] = bombs[j + 1];
            }
            numBombs--;
            break;
        }
    }
    // 检查长度<0（蛇头不计入长度）
    if (nTail < 0) { gameState = GameState::GAME_OVER; return; }
}