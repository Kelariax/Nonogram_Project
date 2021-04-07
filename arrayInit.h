#include "functions.h"

#ifndef ARRAYINIT_H
#define ARRAYINIT_H
int** getMemory(int N, int M, int callocFlag);
int** readDataFromFile(FILE* fp);
int fillCurrentArr(FILE* fsave, int** arrCurrent, int* flagMistakes);
#endif