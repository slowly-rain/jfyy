#include "../common.h"

void spawnFruit() {
    while (true) {
        int fx = rand() % (mWidth - 2) + 1;
        int fy = rand() % (mHeight - 2) + 1;
        if (fx == headX && fy == headY) continue;
        bool coll = false;
        for (int i = 0; i < nTail; i++) if (tailX[i] == fx && tailY[i] == fy) { coll = true; break; }
        if (!coll) { fruitX = fx; fruitY = fy; return; }
    }
}

void spawnBomb() {
    if (numBombs >= MAX_BOMBS) return;
    while (true) {
        int bx = rand() % (mWidth - 2) + 1;
        int by = rand() % (mHeight - 2) + 1;
        if (bx == headX && by == headY) continue;
        bool coll = false;
        for (int i = 0; i < nTail; i++) if (tailX[i] == bx && tailY[i] == by) { coll = true; break; }
        if (bx == fruitX && by == fruitY) coll = true;
        for (int i = 0; i < numBombs; i++) if (bombs[i].x == bx && bombs[i].y == by) { coll = true; break; }
        if (!coll) {
            bombs[numBombs].x = bx;
            bombs[numBombs].y = by;
            bombs[numBombs].spawnTime = clock();
            numBombs++;
            return;
        }
    }
}