#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void set1(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k < bits)) {
        int cells = ((bits - 1) / 8) + 1;
        int byte = k / 8;
        int bit = k % 8;
        if (byte == cells - 1) {
            int tailBits = bits % 8;
            if (tailBits > 0) {
                unsigned char mask = 1;
                mask = mask << 8 - bit;
                vec[byte] = (vec[byte] << 8-tailBits) | mask;
                vec[byte] >>= (8 - tailBits);
                return;
            }
        }
        unsigned char mask = 1;
        mask = mask << 8 - bit;
        vec[byte] = vec[byte] | mask;
    }
}

void set0(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k < bits)) {
        int cells = ((bits - 1) / 8) + 1;
        int byte = k / 8;
        int bit = k % 8;
        if (byte == cells - 1) {
            int tailBits = bits % 8;
            if (tailBits > 0) {
                unsigned char mask = 1;
                mask = mask << 8 - bit;
                mask = ~mask;
                vec[byte] = (vec[byte] << 8 - tailBits) & mask;
                vec[byte] >>= (8 - tailBits);
                return;
            }
        }
        unsigned char mask = 1;
        mask = mask << 8 - bit;
        mask = ~mask;
        vec[byte] = vec[byte] & mask;
    }
}

int main()
{
  //normal set
    // char str[] = "00111111111";
    // int cells = 0;
    // size_t bits = strlen(str);
    // unsigned char* vec = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d \t bits: %d\n", str, cells, bits);
    // printf("StrToBV: ");
    // printBV(vec, cells);

    // set1(vec, bits, 1);
    // printf("Res1:    ");
    // printBV(vec, cells);
    // set0(vec, bits, 1);
    // printf("Res0:    ");
    // printBV(vec, cells);

  //set in tail
    // char str[] = "00111111111";
    // int cells = 0;
    // size_t bits = strlen(str);
    // unsigned char* vec = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d \t bits: %d\n", str, cells, bits);
    // printf("StrToBV: ");
    // printBV(vec, cells);

    // set1(vec, bits, 10);
    // printf("Res1:    ");
    // printBV(vec, cells);
    // set0(vec, bits, 9);
    // printf("Res0:    ");
    // printBV(vec, cells);


    // char str[] = "165488420000001115548";
    // int cells = 0;
    // size_t bits = strlen(str);
    // unsigned char* vec = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d \t bits: %d\n", str, cells, bits);
    // printf("StrToBV: ");
    // printBV(vec, cells);

    // set1(vec, bits, 16);
    // printf("Res1:    ");
    // printBV(vec, cells);
    // set0(vec, bits, 19);
    // printf("Res0:    ");
    // printBV(vec, cells);

    // char str[] = "84787ghguguygb";
    // int cells = 0;
    // size_t bits = strlen(str);
    // unsigned char* vec = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d \t bits: %d\n", str, cells, bits);
    // printf("StrToBV: ");
    // printBV(vec, cells);

    // set1(vec, bits, 10);
    // printf("Res1:    ");
    // printBV(vec, cells);
    // set0(vec, bits, 9);
    // printf("Res0:    ");
    // printBV(vec, cells);



    return 0;
}
