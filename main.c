#include <stdio.h>
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
    if(tailBits != 0) vec[cells - 1] >>= (8 - tailBits);
}
int main()
{
    //normal inversion
    //char str[] = "11110000";
    //char str[] = "08283490jfij4r891092491243";
    //char str[] = "87123908jc1309123=cx1zk121s12312392834ucu0j3134u1092cu4j3c8u124cu9ghfugoiug8urg8egaerg";
    //char str[] = "11111111111111111111000000000000000000000000000";
    //char str[] = "1010001111110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    //tail inversion
    char str[] = "111100011011";
    int cells = 0;
    int bits = strlen(str);
    unsigned char* vec = convertStrToLongBV(str, &cells);
    printf("Original: ");
    printBV(vec, cells);
    //vec is null
    //inversion(NULL, bits);
    //bits is negative size_t 64 bits
    //inversion(vec, -1000);
    inversion(vec, bits);
    printf("Inverted: ");
    printBV(vec, cells);
    return 0;
}

