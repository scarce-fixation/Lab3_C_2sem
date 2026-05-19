#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define vecMaxSize 1000
unsigned char* convertStrToLongBV(char* str, int* cells) {
    if (str && cells) {
        unsigned char mask = 1;
        int len = strlen(str);
        int sI = 0;
        *cells = ((len - 1) / 8) + 1;
        unsigned char* vec = (unsigned char*)calloc(*cells, sizeof(unsigned char));
        for (int i = 0; i < *cells; i++) {
            for (int j = 0; j < 8 && sI < len; j++, sI++) {
                vec[i] = vec[i] << 1;
                if (str[sI] != '0') vec[i] = vec[i] | mask;
            }
        }

        return vec;
    }
    return NULL;
}
char* convertBvToStr(unsigned char* vec, size_t size) {
    char* str = NULL;
    if (vec && size < vecMaxSize) {
        int len = 8*size + 1;
        int i = 0;
        str = (char*)malloc(len);
        if (str) {
            for (int vI = 0; vI < size; vI++) {
                unsigned char mask = 1 << 7;
                for (int j = 0; j < 8 && i < len - 1; j++, i++) {
                    if ((vec[vI] & mask) != 0)str[i] = '1';
                    else str[i] = '0';
                    mask = mask >> 1;
                }
            }
            str[i] = '\0';
        }
        return str;
    }
    return NULL;
}
void printBV(unsigned char* vec, size_t cells) {
    if (vec && cells < vecMaxSize) {
        char* str = convertBvToStr(vec, cells);
        if (str) {
            printf("%s\n", str);
            free(str);
        }
    }
}
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
//normal str
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);
//leading zeroes skip
    char str[] = "0000000000000000000000000111111111";
    int cells = 0;
    unsigned char* vect = convertStrToLongBV(str, &cells);
    printf("Original string is %s \t cells: %d\n", str, cells);
    printf("StrToBV: ");
    printBV(vect, cells);
    char* res = convertBvToStr(vect, cells);
    printf("BvToStr: %s", res);
//big str with letters and symbols
    // char str[] = "4586468251685451841212sfa8sgslkk32@##*&*_$@I#$JN000dsf000123lkksdjf00000234987948/*--+++     sdkjfsknv \n \t ";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);
//empty str
    // char str[] = "";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);
//null str
    // char str[] = "";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(NULL, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);
//null cells
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, NULL);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);

//BvToStr test
//cells > 1000
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(vect, 2000);
    // printf("BvToStr: %s", res);
//null vect
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, cells);
    // char* res = convertBvToStr(NULL, cells);
    // printf("BvToStr: %s", res);

//PrintBV test
//null vect
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(NULL, cells);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);
//cells > 1000
    // char str[] = "00111111111";
    // int cells = 0;
    // unsigned char* vect = convertStrToLongBV(str, &cells);
    // printf("Original string is %s \t cells: %d\n", str, cells);
    // printf("StrToBV: ");
    // printBV(vect, 20000);
    // char* res = convertBvToStr(vect, cells);
    // printf("BvToStr: %s", res);




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

