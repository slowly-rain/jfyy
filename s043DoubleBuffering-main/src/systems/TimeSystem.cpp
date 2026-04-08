#include "../common.h"

void updateBombs() {
    // 检查炸弹过期
    clock_t currentTime = clock();
    for (int i = 0; i < numBombs; ) {
        if ((currentTime - bombs[i].spawnTime) / CLOCKS_PER_SEC >= 5) {
            // 移除炸弹
            for (int j = i; j < numBombs - 1; j++) {
                bombs[j] = bombs[j + 1];
            }
            numBombs--;
        } else {
            i++;
        }
    }
}