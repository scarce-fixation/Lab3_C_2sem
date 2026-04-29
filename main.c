#include <stdio.h>
#include <stdlib.h>
#include<string.h>
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (!vecA && vecB) return vecB;
    if (!vecB && vecA) return vecA;
    if ((!vecA && !vecB) || (bitsA != bitsB)) return NULL;

    int cells = ((bitsA - 1) / 8) + 1;
    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));

    for (int i = 0; i < cells; i++) res[i] = vecA[i] | vecB[i];
    return res;
}
int main()
{
    return 0;
}
