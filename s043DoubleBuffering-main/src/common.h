#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

using namespace std;

constexpr int mWidth = 40;  // 增加宽度以平衡比例
constexpr int mHeight = 20;
constexpr int MAX_TAIL = 256;
const int MAX_BOMBS = 10;

extern HANDLE hOutput1;
extern HANDLE hOutput2;
extern COORD coord;
extern DWORD bytesWritten;
extern bool bufferSwapFlag;
extern char ScreenData[mHeight + 6][mWidth + 6];

enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum class GameState { MENU, RUNNING, PAUSED, GAME_OVER, EXIT };

extern int headX, headY;
extern int fruitX, fruitY;
extern int score;
extern int tailX[MAX_TAIL];
extern int tailY[MAX_TAIL];
extern int nTail;
extern eDirection dir;
extern int difficulty;
extern int speed;

struct Bomb {
    int x, y;
    clock_t spawnTime;
};

extern Bomb bombs[MAX_BOMBS];
extern int numBombs;
extern GameState gameState;

const char* directionToString(eDirection d);
eDirection stringToDirection(const string& s);
bool isOpposite(eDirection a, eDirection b);

int extractInt(const string& src, const string& key, int defaultValue = 0);
string extractString(const string& src, const string& key, const string& defaultValue = "");

// Function declarations
void initConsoleBuffers();
void restoreDefaultBuffer();
void resetGame();
void showMenuScreen();
void showPlayingScreen(bool paused);
void showGameOverScreen();
void processInput();
void updateLogic();
void updateBombs();
void spawnFruit();
void spawnBomb();
bool saveGame(const string& path);
bool loadGame(const string& path);
void drawFrame(bool showHint);
void displayBuffer();