#include "../common.h"

bool saveGame(const string& path) {
    ofstream ofs(path);
    if (!ofs) return false;
    ofs << "{\n";
    ofs << "  \"head\": {\"x\": " << headX << ", \"y\": " << headY << "},\n";
    ofs << "  \"dir\": \"" << directionToString(dir) << "\",\n";
    ofs << "  \"fruit\": {\"x\": " << fruitX << ", \"y\": " << fruitY << "},\n";
    ofs << "  \"score\": " << score << ",\n";
    ofs << "  \"difficulty\": " << difficulty << ",\n";
    ofs << "  \"tail\": [\n";
    for (int i = 0; i < nTail; i++) {
        ofs << "    {\"x\": " << tailX[i] << ", \"y\": " << tailY[i] << "}";
        if (i < nTail - 1) ofs << ",";
        ofs << "\n";
    }
    ofs << "  ],\n";
    ofs << "  \"bombs\": [\n";
    for (int i = 0; i < numBombs; i++) {
        ofs << "    {\"x\": " << bombs[i].x << ", \"y\": " << bombs[i].y << ", \"spawnTime\": " << bombs[i].spawnTime << "}";
        if (i < numBombs - 1) ofs << ",";
        ofs << "\n";
    }
    ofs << "  ]\n";
    ofs << "}\n";
    return true;
}

bool loadGame(const string& path) {
    if (!filesystem::exists(path)) return false;
    ifstream ifs(path);
    if (!ifs) return false;
    string content;
    {
        ostringstream os;
        os << ifs.rdbuf();
        content = os.str();
    }
    int hx = extractInt(content, "\"head\"", headX);
    int hy = extractInt(content, "\"head\"", headY);
    string d = extractString(content, "\"dir\"");
    int fx = extractInt(content, "\"fruit\"", fruitX);
    int fy = extractInt(content, "\"fruit\"", fruitY);
    int sc = extractInt(content, "\"score\"", score);
    int diff = extractInt(content, "\"difficulty\"", difficulty);
    if (hx <= 0 || hx >= mWidth - 1 || hy <= 0 || hy >= mHeight - 1) return false;
    headX = hx;
    headY = hy;
    dir = stringToDirection(d);
    fruitX = fx;
    fruitY = fy;
    score = sc;
    difficulty = diff;
    size_t tailPos = content.find("\"tail\"");
    int loadedTail = 0;
    if (tailPos != string::npos) {
        size_t arrayStart = content.find('[', tailPos);
        size_t arrayEnd = content.find(']', arrayStart);
        if (arrayStart != string::npos && arrayEnd != string::npos) {
            size_t pos = arrayStart + 1;
            while (pos < arrayEnd && loadedTail < MAX_TAIL) {
                size_t xKey = content.find("\"x\"", pos);
                if (xKey == string::npos || xKey > arrayEnd) break;
                int tx = extractInt(content.substr(xKey, arrayEnd - xKey), "\"x\"");
                size_t yKey = content.find("\"y\"", xKey);
                if (yKey == string::npos || yKey > arrayEnd) break;
                int ty = extractInt(content.substr(yKey, arrayEnd - yKey), "\"y\"");
                tailX[loadedTail] = tx;
                tailY[loadedTail] = ty;
                loadedTail++;
                pos = yKey + 1;
            }
        }
    }
    nTail = loadedTail;
    for (int i = nTail; i < MAX_TAIL; i++) { tailX[i] = 0; tailY[i] = 0; }
    // 加载炸弹
    size_t bombPos = content.find("\"bombs\"");
    int loadedBombs = 0;
    if (bombPos != string::npos) {
        size_t arrayStart = content.find('[', bombPos);
        size_t arrayEnd = content.find(']', arrayStart);
        if (arrayStart != string::npos && arrayEnd != string::npos) {
            size_t pos = arrayStart + 1;
            while (pos < arrayEnd && loadedBombs < MAX_BOMBS) {
                size_t xKey = content.find("\"x\"", pos);
                if (xKey == string::npos || xKey > arrayEnd) break;
                int bx = extractInt(content.substr(xKey, arrayEnd - xKey), "\"x\"");
                size_t yKey = content.find("\"y\"", xKey);
                if (yKey == string::npos || yKey > arrayEnd) break;
                int by = extractInt(content.substr(yKey, arrayEnd - yKey), "\"y\"");
                size_t tKey = content.find("\"spawnTime\"", yKey);
                if (tKey == string::npos || tKey > arrayEnd) break;
                clock_t bt = (clock_t)extractInt(content.substr(tKey, arrayEnd - tKey), "\"spawnTime\"");
                bombs[loadedBombs].x = bx;
                bombs[loadedBombs].y = by;
                bombs[loadedBombs].spawnTime = bt;
                loadedBombs++;
                pos = tKey + 1;
            }
        }
    }
    numBombs = loadedBombs;
    for (int i = numBombs; i < MAX_BOMBS; i++) { bombs[i].x = 0; bombs[i].y = 0; bombs[i].spawnTime = 0; }
    return true;
}