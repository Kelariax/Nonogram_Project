#include "arrayInit.h"

int** getMemory(int N, int M, int callocFlag)
{
    int** mas = NULL;
    if (callocFlag == 0)
    {
        mas = (int**)malloc(sizeof(int*) * N);
        for (int i = 0; i < N; i++)
        {
            mas[i] = (int*)malloc(sizeof(int) * M);
        }
    }
    else
    {
        mas = (int**)calloc(N, sizeof(int*));
        for (int i = 0; i < N; i++)
        {
            mas[i] = (int*)calloc(M, sizeof(int));
        }
    }
    return mas;
}

int** readDataFromFile(FILE* fp)
{
    int** arr;
    int N, M;
    int num;
    if (fscanf(fp, "%i", &N) != 1 || fscanf(fp, "%i", &M) != 1)
    {
        printf("ERROR! File damaged\n");
        return NULL;
    }

    arr = getMemory(N, M, 0);
    if (arr == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (fscanf(fp, "%i", &num) != 1)
            {
                printf("ERROR! File damaged\n");
                return NULL;
            }
            else
            {
                arr[i][j] = num;
            }
        }
    }

    return arr;
}

int fillCurrentArr(FILE* fsave, int** arrCurrent, int* flagMistakes)
{
    int flagError = 0, num;
    int sizeN, sizeM;
    sizeN = _msize(arrCurrent) / sizeof(int);
    sizeM = _msize(*arrCurrent) / sizeof(int);
    for (int i = 0; i < sizeN; i++)
    {
        for (int j = 0; j < sizeM; j++)
        {
            if (fscanf(fsave, "%i", &num) != 1)
            {
                flagError = 1;
                return 1;
            }
            else
            {
                if (num == 2)
                {
                    *flagMistakes = 1;
                }
                arrCurrent[i][j] = num;
            }
        }
    }
    return 0;
}