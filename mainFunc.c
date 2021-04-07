#include "mainFunc.h"

void mainFunc()
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    int menuAction, menuStart, saveSelection, savedArr, nonogram;
    int yScreenCoord = 0;
    int** arrTop = NULL;
    int** arrLeft = NULL;
    int** arrRes = NULL;
    int** arrCurrent = NULL;
    FILE* fp = NULL;
    FILE* fsave = NULL;
    int flagMistakes, flagResult, flagBack, flagSave, flagFields, flagRead;
    do
    {
        savedArr = 0;
        saveSelection = 0;
        do
        {
            menuStart = 0;
            nonogram = 0;
            saveSelection = 0;
            printf("1 - Select nonogram\n2 - Load save\n3 - Read rules\n4 - Exit\n");
            printf("Choose variant: ");
            enterNum(&menuStart, 1, 4);
            clearScreen(hout, 0, 0);

            switch (menuStart)
            {
            case 1:
                printf("1 - Nonogram 5x5\n2 - Nonogram 10x10\n3 - Nonogram 15x15\n4 - Nonogram 20x20\n5 - Back to menu\n");
                printf("Choose variant: ");
                enterNum(&nonogram, 1, 5);
                clearScreen(hout, 0, 0);
                fp = switchNonogram(nonogram);
                if (fp == NULL)
                {
                    nonogram = 5;
                }
                break;
            case 2:
                printf("1 - Save File #1\n2 - Save File #2\n3 - Save File #3\n4 - Save File #4\n5 - Back to menu\n");
                printf("Choose variant: ");
                enterNum(&saveSelection, 1, 5);
                clearScreen(hout, 0, 0);
                fsave = switchSave(saveSelection);
                if (fsave == NULL)
                {
                    saveSelection = 5;
                }
                break;
            case 3:
                clearScreen(hout, 0, 0);
                printf("Your aim in these puzzles is to colour the whole grid in to black and white squares.\nBeside each row of the grid are listed the lengths of the runs of black squares on that row.\nAbove each column are listed the lengths of the runs of black squares in that column.\n\n");
                break;
            case 4:
                return 1;
                break;
            }
        } while (menuStart == 3 || nonogram == 5 || saveSelection == 5);

        if (saveSelection > 0)
        {
            if (fsave == NULL)
            {
                displayMessage(hout, "ERROR! File not open\nPress any key to continue...\n", 1);
                continue;
            }
            if ((flagRead = fscanf(fsave, "%i", &nonogram)) == EOF)
            {
                displayMessage(hout, "ERROR! File is empty!\nPress any key to continue...\n", 1);
                fclose(fsave);
                continue;
            }
            if (flagRead == 0 || nonogram <= 0 || nonogram > 4)
            {
                displayMessage(hout, "ERROR! File is damaged!\nPress any key to continue...\n", 1);
                fclose(fsave);
                continue;
            }
            savedArr = nonogram;
        }

        if (savedArr > 0)
        {
            fp = switchNonogram(nonogram);
        }
        if (fp == NULL)
        {
            displayMessage(hout, "ERROR! File not open\nPress any key to continue...\n", 1);
            continue;
        }
        arrTop = readDataFromFile(fp);
        if (arrTop == NULL)
        {
            displayMessage(hout, "ERROR! Memory not allocated\nPress any key to continue...\n", 1);
            fclose(fp);
            continue;
        }
        arrLeft = readDataFromFile(fp);
        if (arrLeft == NULL)
        {
            displayMessage(hout, "ERROR! Memory not allocated\nPress any key to continue...\n", 1);
            fclose(fp);
            continue;
        }
        arrRes = readDataFromFile(fp);
        if (arrRes == NULL)
        {
            displayMessage(hout, "ERROR! Memory not allocated\nPress any key to continue...\n", 1);
            fclose(fp);
            continue;
        }
        fclose(fp);
        arrCurrent = getMemory(_msize(arrRes) / sizeof(int), _msize(*arrRes) / sizeof(int), 1);
        if (arrCurrent == NULL)
        {
            displayMessage(hout, "ERROR! Memory not allocated\nPress any key to continue...\n", 1);
            fclose(fp);
            continue;
        }

        flagResult = flagMistakes = 0;
        if (savedArr > 0)
        {
            int flagError = 0;
            flagError = fillCurrentArr(fsave, arrCurrent, &flagMistakes);
            fclose(fsave);
            if (flagError == 1)
            {
                displayMessage(hout, "ERROR! File is damaged!\nPress any key to continue...\n", 1);
                continue;
            }
            flagResult = resultCheck(arrRes, arrCurrent);
        }

        yScreenCoord = _msize(arrTop) / sizeof(int) + _msize(arrCurrent) / sizeof(int) + 3;
        clearScreen(hout, 0, 0);

        flagBack = flagSave = flagFields = 0;

        if (flagResult == 0)
        {
            do
            {
                menuAction = 0;
                mainOutput(arrTop, arrLeft, arrCurrent);
                if (flagMistakes == 1)
                {
                    char tmp;
                    printf("Enter - Yes\nAny Key - No\nDelete mistakes?\n");
                    tmp = getch();
                    if (tmp == ENTER)
                    {
                        DelMistakes(arrCurrent);
                        flagMistakes = 0;

                        flagResult = resultCheck(arrRes, arrCurrent);
                        if (flagResult == 1)
                        {
                            break;
                        }

                        clearScreen(hout, 0, 0);
                        continue;
                    }
                    else
                    {
                        clearScreen(hout, 0, yScreenCoord);
                    }
                }
                printf("1 - Fill field\n2 - Show mistakes\n3 - Save current solution\n4 - Back to menu\nChoose action: ");
                enterNum(&menuAction, 1, 4);

                clearScreen(hout, 0, yScreenCoord);

                switch (menuAction)
                {
                case 1:
                    flagFields = FillFields(arrCurrent, hout, yScreenCoord);
                    if (flagFields == 1)
                    {

                        clearScreen(hout, 0, 0);
                        continue;
                    }
                    break;
                case 2:
                    flagMistakes = ShowMistakes(arrCurrent, arrRes);
                    if (flagMistakes == 0)
                    {
                        displayMessage(hout, "There are no mistakes!\nPress any key to continue...\n", 0);
                    }
                    break;
                case 3:
                    clearScreen(hout, 0, yScreenCoord);
                    flagSave = resultSave(arrCurrent, nonogram, hout, yScreenCoord);
                    if (flagSave == 0)
                    {
                        clearScreen(hout, 0, 0);
                        continue;
                    }
                    else
                    {
                        clearScreen(hout, 0, yScreenCoord);
                        printf("Success save!\n");
                        printf("Want to continue?\nEnter - Yes\nAny key - No\n");
                        char tmp;
                        tmp = getch();
                        if (tmp == ENTER)
                        {
                            clearScreen(hout, 0, 0);
                            continue;
                        }
                        else
                        {
                            flagBack = 1;
                        }
                    }
                    break;
                case 4:
                    flagBack = 1;
                    break;
                }
                if (flagBack == 1)
                {
                    clearScreen(hout, 0, 0);
                    break;
                }
                flagResult = resultCheck(arrRes, arrCurrent);
                if (flagResult == 1)
                {
                    break;
                }
                clearScreen(hout, 0, 0);
            } while (1);
        }
        if (flagResult == 1)
        {
            clearScreen(hout, 0, 0);
            mainOutput(arrTop, arrLeft, arrCurrent);
            printf("Well done!!!\n");
            displayMessage(hout, "Press any key to see the picture...\n", 1);

            outputPicture(arrCurrent);
            printf("Want to continue?\nEnter - Yes\nAny key - No\n");
            char tmp;
            tmp = getch();
            if (tmp != ENTER)
            {
                int size = _msize(*arrCurrent) / sizeof(int);
                clearScreen(hout, 0, size);
                break;
            }
        }
        clearScreen(hout, 0, 0);
        freeMemory(arrTop);
        freeMemory(arrLeft);
        freeMemory(arrRes);
        freeMemory(arrCurrent);
    } while (1);

    freeMemory(arrTop);
    freeMemory(arrLeft);
    freeMemory(arrRes);
    freeMemory(arrCurrent);
}