#include "common.h"

HANDLE hOutput1 = INVALID_HANDLE_VALUE;
HANDLE hOutput2 = INVALID_HANDLE_VALUE;
COORD coord = {0, 0};
DWORD bytesWritten = 0;
bool bufferSwapFlag = false;
char ScreenData[mHeight + 6][mWidth + 6];

int headX = 0, headY = 0;
int fruitX = 0, fruitY = 0;
int score = 0;
int tailX[MAX_TAIL];
int tailY[MAX_TAIL];
int nTail = 0;
eDirection dir = eDirection::STOP;
int difficulty = 1;
int speed = 100;

Bomb bombs[MAX_BOMBS];
int numBombs = 0;
GameState gameState = GameState::MENU;

const char* directionToString(eDirection d) {
    switch (d) {
        case eDirection::LEFT: return "LEFT";
        case eDirection::RIGHT: return "RIGHT";
        case eDirection::UP: return "UP";
        case eDirection::DOWN: return "DOWN";
        default: return "STOP";
    }
}

eDirection stringToDirection(const string& s) {
    if (s == "LEFT") return eDirection::LEFT;
    if (s == "RIGHT") return eDirection::RIGHT;
    if (s == "UP") return eDirection::UP;
    if (s == "DOWN") return eDirection::DOWN;
    return eDirection::STOP;
}

bool isOpposite(eDirection a, eDirection b) {
    return (a == eDirection::LEFT && b == eDirection::RIGHT) ||
           (a == eDirection::RIGHT && b == eDirection::LEFT) ||
           (a == eDirection::UP && b == eDirection::DOWN) ||
           (a == eDirection::DOWN && b == eDirection::UP);
}

int extractInt(const string& src, const string& key, int defaultValue) {
    auto pos = src.find(key);
    if (pos == string::npos) return defaultValue;
    pos = src.find(':', pos);
    if (pos == string::npos) return defaultValue;
    pos++;
    while (pos < src.size() && (isspace((unsigned char)src[pos]) || src[pos] == '"' || src[pos] == ',' || src[pos] == '{' || src[pos] == '[')) pos++;
    if (pos >= src.size() || (!isdigit((unsigned char)src[pos]) && src[pos] != '-')) return defaultValue;
    size_t end = pos;
    if (src[end] == '-') end++;
    while (end < src.size() && isdigit((unsigned char)src[end])) end++;
    if (end == pos) return defaultValue;
    return stoi(src.substr(pos, end - pos));
}

string extractString(const string& src, const string& key, const string& defaultValue) {
    auto pos = src.find(key);
    if (pos == string::npos) return defaultValue;
    pos = src.find(':', pos);
    if (pos == string::npos) return defaultValue;
    pos = src.find('"', pos);
    if (pos == string::npos) return defaultValue;
    auto end = src.find('"', pos + 1);
    if (end == string::npos) return defaultValue;
    return src.substr(pos + 1, end - pos - 1);
}