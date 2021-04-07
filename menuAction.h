#include "functions.h"
#include "outputFunctions.h"

#ifndef MENUACTION_H
#define MENUACTION_H
int FillFields(int** arrCurrent, HANDLE hout, int yScreenCoord);
int ShowMistakes(int** arrCurrent, int** arrRes);
void DelMistakes(int** arrCurrent);
int resultSave(int** arrCurrent, int nonogram, HANDLE hout, int yScreenCoord);
#endif
