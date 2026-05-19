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
int main()
{
    printf("Hello World!\n");
    return 0;
}
