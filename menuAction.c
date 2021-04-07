#include "menuAction.h"

int FillFields(int** arrCurrent, HANDLE hout, int yScreenCoord)
{
    int start, num, flagBack;
    int x, y;
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);

    do
    {
        flagBack = 0;
        printf("1 - Fill one field\n2 - Fill fields in line\n3 - Back\nChoose action: ");
        enterNum(&start, 1, 3);
        clearScreen(hout, 0, yScreenCoord);
        switch (start)
        {
        case 1:
            printf("Enter coordinates (x,y):\n");
            printf("x = ");
            enterNum(&x, 1, currSizeM);
            x -= 1;
            printf("y = ");
            enterCoordinatesY(&y, currSizeM);
            arrCurrent[y][x] = 1;
            break;
        case 2:
            printf("1 - Vertical Line\n2 - Horizontal Line\n3 - Back\nChoose variant: ");
            enterNum(&num, 1, 3);
            clearScreen(hout, 0, yScreenCoord);
            if (num == 3)
            {
                break;
            }
            switch (num)
            {
            case 1:
                printf("Enter first coordinates(x1,y1): \n");
                printf("x = ");
                enterNum(&x, 1, currSizeM);
                x -= 1;
                printf("y = ");
                enterCoordinatesY(&y, currSizeM);
                int y2;
                printf("Enter second coordinates(y2): \n");
                printf("y2 = ");
                enterCoordinatesY(&y2, currSizeM);
                if (y2 > y)
                {
                    for (int i = y; i <= y2; i++)
                    {
                        arrCurrent[i][x] = 1;
                    }
                }
                else
                {
                    for (int i = y2; i <= y; i++)
                    {
                        arrCurrent[i][x] = 1;
                    }
                }
                break;
            case 2:
                printf("Enter first coordinates(x1,x2): \n");
                printf("x = ");
                enterNum(&x, 1, currSizeM);
                x -= 1;
                int x2;
                printf("x2 = ");
                enterNum(&x2, 1, currSizeM);
                x2 -= 1;
                printf("y = ");
                enterCoordinatesY(&y, currSizeM);
                if (x2 > x)
                {
                    for (int i = x; i <= x2; i++)
                    {
                        arrCurrent[y][i] = 1;
                    }
                }
                else
                {
                    for (int i = x2; i <= x; i++)
                    {
                        arrCurrent[y][i] = 1;
                    }
                }
                clearScreen(hout, 0, yScreenCoord);
                break;
            }
            break;
        case 3: return 1; break;
        }
        if (flagBack == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    } while (1);
}

int ShowMistakes(int** arrCurrent, int** arrRes)
{
    int flag = 0;
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    for (int i = 0; i < currSizeN; i++)
    {
        for (int j = 0; j < currSizeM; j++)
        {
            if (arrCurrent[i][j] != 0 && arrCurrent[i][j] != arrRes[i][j])
            {
                arrCurrent[i][j] = 2;
                flag = 1;
            }
        }
    }
    return flag;
}

void DelMistakes(int** arrCurrent)
{
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    for (int i = 0; i < currSizeN; i++)
    {
        for (int j = 0; j < currSizeM; j++)
        {
            if (arrCurrent[i][j] == 2)
            {
                arrCurrent[i][j] = 0;
            }
        }
    }
}

int resultSave(int** arrCurrent, int nonogram, HANDLE hout, int yScreenCoord)
{
    int currSizeN, currSizeM;
    currSizeN = _msize(arrCurrent) / sizeof(int);
    currSizeM = _msize(*arrCurrent) / sizeof(int);
    int save, flag = 0;
    char symb;
    FILE* fs = NULL;
    for (int i = 0; i < currSizeN; i++)
    {
        for (int j = 0; j < currSizeM; j++)
        {
            if (arrCurrent[i][j] == 0)
            {
                flag = 0;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
    if (flag == 0)
    {
        displayMessage(hout, "ERROR! Your solution is empty!\nPress any key to continue...\n", 0);
        return 0;
    }
    do
    {
        printf("1 - Save File #1\n2 - Save File #2\n3 - Save File #3\n4 - Save File #4\n5 - Back\n");
        printf("Choose variant: ");
        enterNum(&save, 1, 5);
        switch (save)
        {
        case 1:
            fs = fopen("saves\\save1.txt", "r+"); break;
        case 2:
            fs = fopen("saves\\save2.txt", "r+"); break;
        case 3:
            fs = fopen("saves\\save3.txt", "r+"); break;
        case 4:
            fs = fopen("saves\\save4.txt", "r+"); break;
        case 5:
            return 0;
            break;
        }
        if (fs == NULL)
        {
            displayMessage(hout, "ERROR! File not open\nPress any key to continue...\n", 0);
            return 0;
        }
        if (fscanf(fs, "%i") == 1)
        {
            clearScreen(hout, 0, yScreenCoord);
            rewind(fs);
            printf("This save already has the data. Want to rewrite it?\nEnter - Yes\nAny key - No\n");
            symb = getch();
            if (symb != 13)
            {
                fclose(fs);
                clearScreen(hout, 0, yScreenCoord);
                continue;
            }
        }
        fprintf(fs, "%i ", nonogram);
        for (int i = 0; i < currSizeN; i++)
        {
            for (int j = 0; j < currSizeM; j++)
            {
                fprintf(fs, "%i ", arrCurrent[i][j]);
            }
        }
        break;
    } while (1);
    clearScreen(hout, 0, yScreenCoord);
    fclose(fs);
    return 1;
}