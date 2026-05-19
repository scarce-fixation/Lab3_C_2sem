#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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
int main()
{
    printf("Hello World!\n");
    return 0;
}
