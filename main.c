#include <stdio.h>
#include<stdlib.h>
#define vecMaxSize 1000
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
