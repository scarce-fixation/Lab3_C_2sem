#include <stdio.h>
#include <stdlib.h>
#include<string.h>

unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if ((!vecA && !vecB) || (bitsA != bitsB)) return NULL;
    if (!vecA) return vecB;
    if (!vecB) return vecA;

    int cells = ((bitsA - 1) / 8) + 1;

    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));

    for (int i = 0; i < cells; i++) res[i] = vecA[i] ^ vecB[i];
    return res;
}
int main()
{
    printf("Hello World!\n");
    return 0;
}
