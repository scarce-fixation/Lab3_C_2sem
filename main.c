#include <stdio.h>
#include<stdlib.h>
#define vecMaxSize 1000
void printBV(unsigned char* vec, size_t cells) {
    if (vec && cells < vecMaxSize) {
        char* str = convertBvToStr(vec, cells);
        if (str) {
            printf("%s\n", str);
            free(str);
        }
    }
}
int main()
{
    printf("Hello World!\n");
    return 0;
}
