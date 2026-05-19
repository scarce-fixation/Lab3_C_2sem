#include <stdio.h>
#include <stdlib.h>
#include<string.h>
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (vecA == NULL && vecB) return vecB;
    if (vecB == NULL && vecA) return vecA;
    if ((vecA == NULL && vecB == NULL) || (bitsA != bitsB)) return NULL;
    int cells = ((bitsA - 1) / 8) + 1;
    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));
    for (int i = 0; i < cells; i++) res[i] = vecA[i] & vecB[i];
    return res;
}

int main()
{
//normal mul
    // char strA[] = "00111111111";
    // int cellsA = 0;
    // char strB[] = "00111111111";
    // int cellsB = 0;
    // unsigned char* vecA = convertStrToLongBV(strA, &cellsA);
    // unsigned char* vecB = convertStrToLongBV(strB, &cellsB);
    // size_t bitsA = strlen(strA);
    // size_t bitsB = strlen(strB);
    // printf("StringA is %s\t cells: %d\nStringB is %s \t cells: %d\n", strA, cellsA, strB, cellsB);
    // printf("\nvecA is ");
    // printBV(vecA, cellsA);
    // printf("vecB is ");
    // printBV(vecB, cellsB);
    // unsigned char* res = logMul(vecA, bitsA, vecB, bitsB);
    // printf("\nRes is  ");
    // printBV(res, cellsA);

    // char strA[] = "10101111101";
    // int cellsA = 0;
    // char strB[] = "00111010110";
    // int cellsB = 0;
    // unsigned char* vecA = convertStrToLongBV(strA, &cellsA);
    // unsigned char* vecB = convertStrToLongBV(strB, &cellsB);
    // size_t bitsA = strlen(strA);
    // size_t bitsB = strlen(strB);
    // printf("StringA is %s\t cells: %d\nStringB is %s \t cells: %d\n", strA, cellsA, strB, cellsB);
    // printf("\nvecA is ");
    // printBV(vecA, cellsA);
    // printf("vecB is ");
    // printBV(vecB, cellsB);
    // unsigned char* res = logMul(vecA, bitsA, vecB, bitsB);
    // printf("\nRes is  ");
    // printBV(res, cellsA);
//vecA is null
    // char strA[] = "10101111101";
    // int cellsA = 0;
    // char strB[] = "00111010110";
    // int cellsB = 0;

    // unsigned char* vecA = convertStrToLongBV(strA, &cellsA);
    // unsigned char* vecB = convertStrToLongBV(strB, &cellsB);
    // size_t bitsA = strlen(strA);
    // size_t bitsB = strlen(strB);

    // printf("StringA is %s\t cells: %d\nStringB is %s \t cells: %d\n", strA, cellsA, strB, cellsB);

    // printf("\nvecA is ");
    // printBV(vecA, cellsA);
    // printf("vecB is ");
    // printBV(vecB, cellsB);
    // unsigned char* res = logMul(NULL, bitsA, vecB, bitsB);
    // printf("\nRes is  ");
    // printBV(res, cellsA);
//vecB is null
    // char strA[] = "10101111101";
    // int cellsA = 0;
    // char strB[] = "00111010110";
    // int cellsB = 0;

    // unsigned char* vecA = convertStrToLongBV(strA, &cellsA);
    // unsigned char* vecB = convertStrToLongBV(strB, &cellsB);
    // size_t bitsA = strlen(strA);
    // size_t bitsB = strlen(strB);

    // printf("StringA is %s\t cells: %d\nStringB is %s \t cells: %d\n", strA, cellsA, strB, cellsB);

    // printf("\nvecA is ");
    // printBV(vecA, cellsA);
    // printf("vecB is ");
    // printBV(vecB, cellsB);
    // unsigned char* res = logMul(vecA, bitsA, NULL, bitsB);
    // printf("\nRes is  ");
    // printBV(res, cellsA);

//length differ
    // char strA[] = "10101111101111111111111111111111";
    // int cellsA = 0;
    // char strB[] = "00111010110";
    // int cellsB = 0;

    // unsigned char* vecA = convertStrToLongBV(strA, &cellsA);
    // unsigned char* vecB = convertStrToLongBV(strB, &cellsB);
    // size_t bitsA = strlen(strA);
    // size_t bitsB = strlen(strB);

    // printf("StringA is %s\t cells: %d\nStringB is %s \t cells: %d\n", strA, cellsA, strB, cellsB);

    // printf("\nvecA is ");
    // printBV(vecA, cellsA);
    // printf("vecB is ");
    // printBV(vecB, cellsB);
    // unsigned char* res = logMul(vecA, bitsA, vecB, bitsB);
    // printf("\nRes is  ");
    // printBV(res, cellsA);

    return 0;
}

