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
    printf("Hello World!\n");
    return 0;
}
