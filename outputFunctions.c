#include "outputFunctions.h"

void displayMessage(HANDLE hout, char message[], int clearScreenFlag)
{
    printf("%s", message);
    getch();
    if (clearScreenFlag == 1)
    {
        clearScreen(hout, 0, 0);
    }
}

void mainOutput(int** arrTop, int** arrLeft, int** arrCurrent)
{
    int topSizeN, topSizeM;
    topSizeN = _msize(arrTop) / sizeof(int);
    topSizeM = _msize(*arrTop) / sizeof(int);
    int leftSizeN, leftSizeM;
    leftSizeN = _msize(arrLeft) / sizeof(int);
    leftSizeM = _msize(*arrLeft) / sizeof(int);
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    int length = topSizeM + leftSizeM;

    for (int i = 0; i < topSizeN; i++)
    {
        for (int s = 0; s < leftSizeM; s++)
        {
            printf("%3c", SPACE);
        }
        printf("|");
        for (int j = 0; j < topSizeM; j++)
        {
            printf("%2i ", arrTop[i][j]);
        }
        printf("%c|\n", BACKSPACE);
    }
    for (int i = 0; i <= length; i++)
    {
        printf("%c%c ", MINUS, MINUS);
    }
    printf(" \n");
    char x = 'A';
    for (int i = 0; i < leftSizeN; i++)
    {
        for (int j = 0; j < leftSizeM; j++)
        {
            printf("%2i ", arrLeft[i][j]);
        }
        printf("|");
        for (int c = 0; c < currSizeM; c++)
        {
            if (arrCurrent[i][c] == 0)
            {
                printf("%2c|", SPACE);
            }
            else if (arrCurrent[i][c] == 1)
            {
                printf("%2c|", SHARP);
            }
            else
            {
                printf("%2c|", EXCmark);
            }
        }
        printf("%c\n", x);
        x++;
    }
    for (int i = 0; i <= length; i++)
    {
        printf("%c%c ", MINUS, MINUS);
    }
    printf("\n");
    for (int s = 0; s < leftSizeM; s++)
    {
        printf("%3c", SPACE);
    }
    printf("|");
    for (int i = 1; i <= currSizeM; i++)
    {
        printf("%2i|", i);
    }
    printf("\n");
}

void outputPicture(int** arrCurrent)
{
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    for (int i = 0; i < currSizeN; i++)
    {
        for (int j = 0; j < currSizeM; j++)
        {
            if (arrCurrent[i][j] == 0)
            {
                printf("%2c", SPACE);
            }
            else if (arrCurrent[i][j] == 1)
            {
                printf("%2c", SHARP);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void clearScreen(HANDLE hConsole, int x, int y)
{
    COORD coordScreen;
    coordScreen.X = x;
    coordScreen.Y = y;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole,
        (TCHAR)' ',
        dwConSize,
        coordScreen,
        &cCharsWritten))
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole,
        csbi.wAttributes,
        dwConSize,
        coordScreen,
        &cCharsWritten))
    {
        return;
    }

    SetConsoleCursorPosition(hConsole, coordScreen);
}