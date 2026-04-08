#include "../common.h"

void resetGame() {
    dir = eDirection::STOP;
    score = 0;
    nTail = 0;
    difficulty = 1;
    speed = 100;
    numBombs = 0;
    headX = mWidth / 2;
    headY = mHeight / 2;
    for (int i = 0; i < MAX_TAIL; i++) { tailX[i] = 0; tailY[i] = 0; }
    srand(static_cast<unsigned>(time(nullptr)));
    spawnFruit();
}

void showMenuScreen() {
    restoreDefaultBuffer();
    system("cls");
    cout << "##########################################\n";
    cout << "#      控制台贪吃蛇（双缓冲实现）       #\n";
    cout << "##########################################\n";
    cout << "N: 新游戏  L: 读取存档  Q: 退出\n";
    cout << "方向键或 WASD 控制，SPACE 暂停/继续\n";
    cout << "F: 水果  B: 炸弹（吃到减少长度）\n";
    cout << "难度随得分自动增加，难度越高炸弹越多\n";
    cout << "速度随得分自动加快（分数越高越快）\n";
    cout << "游戏结束：碰到墙或长度<0\n";
    cout << "请选择: ";
}

void showGameOverScreen() {
    drawFrame(false);
    string msg = "GAME OVER! Score:" + to_string(score) + " [R]重开 [M]菜单 [Q]退出 [Z]存档";
    int row = mHeight + 1;
    for (int i = 0; i < mWidth; i++) ScreenData[row][i] = i < (int)msg.size() ? msg[i] : ' ';
    displayBuffer();
}