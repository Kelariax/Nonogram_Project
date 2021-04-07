#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
FILE* switchSave(int saveSelection);
FILE* switchNonogram(int nonogram);
void enterNum(int* num, int from, int too);
void enterCoordinatesY(int* y, int currSizeM);
void freeMemory(int** arr);
int resultCheck(int** arrRes, int** arrCurrent);
#endif