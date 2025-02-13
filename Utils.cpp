#include "Utils.h"
#include "Point.h"
#include <iostream>
#include <random>
#include <windows.h>

void gotop(Point p) {
    gotoxy(p.x, p.y);
}
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = x; // Set the X coordinate 
    coord.Y = y; // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
bool getRandomBoolean() {
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    // Generate a random true (1) or false (0)
    return dis(gen);
}

bool getFivePercentBoolean() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // 5% chance
    return dis(gen) >= 0.95;
}
