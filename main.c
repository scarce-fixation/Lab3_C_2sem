#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void set1(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k < bits)) {
        int byte = k / 8;
        int bit = k % 8;
        unsigned char mask = 1;
        mask = mask << 8 - bit;
        vec[byte] = vec[byte] | mask;
    }
}

void set0(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k < bits)) {
        int byte = k / 8;
        int bit = k % 8;
        unsigned char mask = 1;
        mask = mask << 8 - bit;
        mask = ~mask;
        vec[byte] = vec[byte] & mask;
    }
}

int main()
{
    printf("Hello World!\n");
    return 0;
}
