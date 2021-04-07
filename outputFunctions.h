#include "functions.h"
#define SPACE 32
#define BACKSPACE 8
#define MINUS 45
#define SHARP 35
#define EXCmark 33

#ifndef OUTPUTFUNCTIONS_H
#define OUTPUTFUNCTIONS_H
void displayMessage(HANDLE hout, char message[], int clsFlag);
void mainOutput(int** arrTop, int** arrLeft, int** arrCurrent);
void outputPicture(int** arrCurrent);
void clearScreen(HANDLE hConsole, int x, int y);
#endif