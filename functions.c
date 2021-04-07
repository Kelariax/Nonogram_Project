#include "functions.h"

FILE* switchNonogram(int nonogram)
{
    FILE* fp = NULL;
    switch (nonogram)
    {
    case 1:
        fp = fopen("nonograms\\nonogram1.txt", "r"); break;
    case 2:
        fp = fopen("nonograms\\nonogram2.txt", "r"); break;
    case 3:
        fp = fopen("nonograms\\nonogram3.txt", "r"); break;
    case 4:
        fp = fopen("nonograms\\nonogram4.txt", "r"); break;
    case 5: break;
    }

    return fp;
}

FILE* switchSave(int saveSelection)
{
    FILE* fsave = NULL;
    switch (saveSelection)
    {
    case 1:
        fsave = fopen("saves\\save1.txt", "r"); break;
    case 2:
        fsave = fopen("saves\\save2.txt", "r"); break;
    case 3:
        fsave = fopen("saves\\save3.txt", "r"); break;
    case 4:
        fsave = fopen("saves\\save4.txt", "r"); break;
    case 5: break;
    }

    return fsave;
}

void enterNum(int* num, int from, int too)
{
    do
    {
        if (scanf("%i", num) != 1)
        {
            scanf("%*s");
        }
        if (*num >= from && *num <= too)
        {
            break;
        }
        printf("Wrong input data!\nTry again: ");
    } while (1);
}

void enterCoordinatesY(int* y, int currSizeM)
{
    char symbY, g;
    do
    {
        while ((g = getc(stdin)) != '\n');
        scanf("%c", &symbY);

        if (symbY > 64 && symbY <= 64 + currSizeM)
        {
            *y = (int)symbY - 65;
            break;
        }
        else if (symbY > 96 && symbY <= 96 + currSizeM)
        {
            *y = (int)symbY - 97;
            break;
        }
        printf("Wrong input data!\nTry again: ");
    } while (1);
}


void freeMemory(int** arr)
{
    int SizeN;
    SizeN = _msize(arr) / sizeof(int);
    for (int i = 0; i < SizeN; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int resultCheck(int** arrRes, int** arrCurrent)
{
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    for (int i = 0; i < currSizeN; i++)
    {
        for (int j = 0; j < currSizeM; j++)
        {
            if (arrCurrent[i][j] != arrRes[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}