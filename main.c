#include <stdio.h>
#include <stdlib.h>
#include<string.h>
unsigned char* convertStrToLongBV(char* str, int* cells) {
    if (str && cells) {

        int len = strlen(str);
        int sI = 0;
        *cells = ((len - 1) / 8) + 1;
        unsigned char* vec = (unsigned char*)calloc(*cells, sizeof(unsigned char));
        for (int i = 0; i < *cells; i++) {
            unsigned char mask = 1 << 7;
            for (int j = 0; j < 8 && sI < len; j++, sI++) {
                if (str[sI] != '0') vec[i] = vec[i] | mask;
                mask >>= 1;
            }
        }
        return vec;
    }
    return NULL;
}
char* convertBvToStr(unsigned char* vec, size_t size) {
    char* str = NULL;
    if (vec) {
        int len = 8 * size + 1;
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
// itoa integer to ascii
// char buffer[9];
// itoa(val, buffer, 2); // 2 = base
// printf("%s", buffer);
void printBV(unsigned char* vec, size_t cells) {
    if (vec && cells !=0) {
        int len = 8 * cells + 1;
        int i = 0;
        for (int vI = 0; vI < cells; vI++) {
            unsigned char mask = 1 << 7;
            for (int j = 0; j < 8 && i < len - 1; j++, i++) {
                if ((vec[vI] & mask) != 0)printf("1");
                else printf("0");
                mask = mask >> 1;
            }
        }
        printf("\n");
    }
}
void set1(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k <= bits)) {
        int byte = k / 8;
        int bit = k % 8;
        unsigned char mask = 1;
        mask = mask << (8 - bit);
        vec[byte] = vec[byte] | mask;
    }
}
void set0(unsigned char* vec, size_t bits, size_t k) {
    if (vec && (k > 0 && k <= bits)) {
        int byte = k / 8;
        int bit = k % 8;
        unsigned char mask = 1;
        mask = mask << (8 - bit);
        mask = ~mask;
        vec[byte] = vec[byte] & mask;
    }
}
unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if ((!vecA && !vecB) || (bitsA != bitsB)) return NULL;
    if (!vecA) return vecB;
    if (!vecB) return vecA;
    int cells = ((bitsA - 1) / 8) + 1;
    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));
    for (int i = 0; i < cells; i++) res[i] = vecA[i] ^ vecB[i];
    return res;
}
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (!vecA && vecB) return vecB;
    if (!vecB && vecA) return vecA;
    if ((!vecA && !vecB) || (bitsA != bitsB)) return NULL;
    int cells = ((bitsA - 1) / 8) + 1;
    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));
    for (int i = 0; i < cells; i++) res[i] = vecA[i] | vecB[i];
    return res;
}
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (vecA == NULL && vecB) return vecB;
    if (vecB == NULL && vecA) return vecA;
    if ((vecA == NULL && vecB == NULL) || (bitsA != bitsB)) return NULL;
    int cells = ((bitsA - 1) / 8) + 1;
    unsigned char* res = (unsigned char*)calloc(cells, sizeof(unsigned char));
    for (int i = 0; i < cells; i++) res[i] = vecA[i] & vecB[i];
    return res;
}
void shiftLeft(unsigned char* vec, size_t bits, size_t k) {
    if (!vec || bits <= 0 || k <= 0) return;
    int cells = ((bits - 1) / 8) + 1;
    if (k >= bits) {
        for (int j = 0; j < cells; j++) vec[j] = 0;
        return;
    }
    int byteShift = k / 8;
    int bitShift = k % 8;
    if (byteShift > 0) {
        int i = 0;
        for (; i < cells - byteShift; i++) {
            vec[i] = vec[i + byteShift];
        }
        for (; i < cells; i++) {
            vec[i] = 0;
        }
    }

    if (bitShift > 0) {
        unsigned char carry = 0;
        int i = cells - 1 - byteShift;
        unsigned char tail = 0;
        tail = vec[i];

        carry = tail >> (8 - bitShift);
        tail = tail << bitShift;

        vec[i] = tail;
        i--;
        for (; i >= 0; i--) {
            unsigned char nextCarry = vec[i] >> (8 - bitShift);
            vec[i] = (vec[i] << bitShift) | carry;
            carry = nextCarry;
        }
    }
}

void inversion(unsigned char* vec, size_t bits) {
    if (!vec) return;
    int cells = (bits - 1) / 8 + 1;
    for (int i = 0; i < cells; i++) {
        unsigned char result = 0;
        for (int j = 0; j < 8; j++) {
            result = (result << 1) | (vec[i] & 1);
            vec[i] >>= 1;
        }
        vec[i] = ~result;
    }
    int tailBits = bits % 8;
    if (tailBits != 0) vec[cells - 1] <<= (8 - tailBits);
}
void shiftRight(unsigned char* vec, size_t bits, size_t k) {
    if (!vec || bits <= 0 || k <= 0) return;
    int cells = ((bits - 1) / 8) + 1;
    if (k >= bits) {
        for (int i = 0; i < cells; i++) vec[i] = 0;
        return;
    }
    int tailBits = bits % 8;
    int byteShift = k / 8;
    int bitShift = k % 8;
    if (byteShift > 0) {
        for (int i = cells - 1; i >= byteShift; i--) {
            vec[i] = vec[i - byteShift];
        }
        for (int i = 0; i < byteShift; i++) {
            vec[i] = 0;
        }
        k = k - tailBits;
        bitShift = k % 8;
    }


    if (bitShift > 0) {
        unsigned char carry = 0;
        int i = byteShift;
        for (; i < cells - 1; i++) {
            unsigned char nextCarry = vec[i] << (8 - bitShift);
            vec[i] = (vec[i] >> bitShift) | carry;
            carry = nextCarry;
        }

        if (byteShift > 0 || tailBits == 0) {
            vec[i] = (vec[i] >> bitShift) | carry;
        }
        else {
            vec[i] = vec[i] >> bitShift;
            vec[i] = carry | vec[i];
            vec[i] = vec[i] >> (8 - tailBits);
            vec[i] = (vec[i] << (8 - tailBits));
        }
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
    //leading zeroes
        // char str[] = "0000000000000000000000000111111111";
        // int cells = 0;
        // unsigned char* vect = convertStrToLongBV(str, &cells);
        // printf("Original string is %s \t cells: %d\n", str, cells);
        // printf("StrToBV: ");
        // printBV(vect, cells);
        // char* res = convertBvToStr(vect, cells);
        // printf("BvToStr: %s", res);
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


    //SET

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

    //SUM

    //normal sum
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
        // unsigned char* res = sumMod2(vecA, bitsA, vecB, bitsB);
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
        // unsigned char* res = sumMod2(vecA, bitsA, vecB, bitsB);
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
        // unsigned char* res = sumMod2(NULL, bitsA, vecB, bitsB);
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
        // unsigned char* res = sumMod2(vecA, bitsA, NULL, bitsB);
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
        // unsigned char* res = sumMod2(vecA, bitsA, vecB, bitsB);
        // printf("\nRes is  ");
        // printBV(res, cellsA);

    //normal sum
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
        // unsigned char* res = logSum(vecA, bitsA, vecB, bitsB);
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
        // unsigned char* res = logSum(vecA, bitsA, vecB, bitsB);
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
        // unsigned char* res = logSum(NULL, bitsA, vecB, bitsB);
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
        // unsigned char* res = logSum(vecA, bitsA, NULL, bitsB);
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
        // unsigned char* res = logSum(vecA, bitsA, vecB, bitsB);
        // printf("\nRes is  ");
        // printBV(res, cellsA);

    //MUL

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

    //INVERSION


        //normal inversion
    char str[] = "111111111";
    //char str[] = "08283490jfij4r891092491243";
    //char str[] = "87123908jc1309123=cx1zk121s12312392834ucu0j3134u1092cu4j3c8u124cu9ghfugoiug8urg8egaerg";
    //char str[] = "11111111111111111111000000000000000000000000000";
    //char str[] = "1010001111110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    //tail inversion
    //char str[] = "111100011011";


    int cells = 0;
    int bits = strlen(str);
    unsigned char* vec = convertStrToLongBV(str, &cells);


    // printf("Original: ");
    // printBV(vec, cells);
    // //vec is null
    // //inversion(NULL, bits);
    // //bits is negative size_t 64 bits
    // //inversion(vec, -1000);
    // inversion(vec, bits);
    // printf("Inverted: ");
    // printBV(vec, cells);

//SHIFTRIGHT

    //normal shift
    printf("Original: ");
    printBV(vec, cells);

    int k = 2;

    shiftRight(vec, bits, k);
    //shift >= bits
    //shiftRight(vec, bits, bits + 100);
    printf("Shifted : ");
    printBV(vec, cells);

    //SHIFTLEFT

        //normal shift
        // printf("Original: ");
        // printBV(vec, cells);

        // int k = 2;

        // shiftLeft(vec, bits, k);
        // //shift >= bits
        // //shiftLeft(vec, bits, bits + 100);
        // printf("Shifted : ");
        // printBV(vec, cells);
    return 0;
}

