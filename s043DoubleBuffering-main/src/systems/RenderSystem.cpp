#include "../common.h"

void drawFrame(bool showHint = false) {
    int row = 0;
    // 上边框：+-------+
    ScreenData[row][0] = '+';
    for (int j = 1; j < mWidth - 1; j++) ScreenData[row][j] = '-';
    ScreenData[row][mWidth - 1] = '+';
    row++;
    // 中间行：竖边|，中间空格
    for (int y = 1; y < mHeight - 1; y++) {
        ScreenData[row][0] = '|';
        for (int x = 1; x < mWidth - 1; x++) ScreenData[row][x] = ' ';
        ScreenData[row][mWidth - 1] = '|';
        row++;
    }
    // 下边框：+-------+
    ScreenData[row][0] = '+';
    for (int j = 1; j < mWidth - 1; j++) ScreenData[row][j] = '-';
    ScreenData[row][mWidth - 1] = '+';
    row++;
    string info = to_string(score) + " D:" + to_string(difficulty) + " S:" + to_string(speed);
    for (int i = 0; i < mWidth; i++) ScreenData[row][i] = i < (int)info.size() ? info[i] : ' ';
    row++;
    string hint = showHint ? "[SPACE][M][Q][Z]" : "[SPACE][Z][Q]";
    for (int i = 0; i < mWidth; i++) ScreenData[row][i] = i < (int)hint.size() ? hint[i] : ' ';
    if (fruitX > 0 && fruitX < mWidth - 1 && fruitY > 0 && fruitY < mHeight - 1) ScreenData[fruitY][fruitX] = 'F';
    if (headX > 0 && headX < mWidth - 1 && headY > 0 && headY < mHeight - 1) ScreenData[headY][headX] = 'O';
    for (int i = 0; i < nTail; i++) {
        int tx = tailX[i], ty = tailY[i];
        if (tx > 0 && tx < mWidth - 1 && ty > 0 && ty < mHeight - 1) ScreenData[ty][tx] = 'o';
    }
    for (int i = 0; i < numBombs; i++) {
        if (bombs[i].x > 0 && bombs[i].x < mWidth - 1 && bombs[i].y > 0 && bombs[i].y < mHeight - 1) {
            ScreenData[bombs[i].y][bombs[i].x] = 'B';
        }
    }
}

void displayBuffer() {
    int totalRows = mHeight + 2;
    HANDLE wall = bufferSwapFlag ? hOutput2 : hOutput1;
    for (int i = 0; i < totalRows; i++) {
        coord.X = 0;
        coord.Y = i;
        WriteConsoleOutputCharacterA(wall, ScreenData[i], mWidth, coord, &bytesWritten);
    }
    SetConsoleActiveScreenBuffer(wall);
    bufferSwapFlag = !bufferSwapFlag;
}

void showPlayingScreen(bool paused = false) {
    drawFrame(paused);
    displayBuffer();
}