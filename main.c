#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void shiftRight(unsigned char* vec, size_t bits, size_t k) {
    if (!vec || bits <= 0 || k <= 0) return;
    int cells = ((bits - 1) / 8) + 1;
    if (k >= bits) {
        for (int i = 0; i < cells; i++) vec[i] = 0;
        return;
    }
    int byteShift = k / 8;
    int bitShift = k % 8;
    if (byteShift > 0) {
        for (int i = cells - 1; i >= byteShift; i--) {
            vec[i] = vec[i - byteShift];
        }
        for (int i = 0; i < byteShift; i++) {
            vec[i] = 0;
        }
    }
    if (bitShift > 0) {
        unsigned char carry = 0;
        int i = byteShift;
        for (; i < cells - 1; i++) {
            unsigned char nextCarry = vec[i] << (8 - bitShift);
            vec[i] = (vec[i] >> bitShift) | carry;
            carry = nextCarry;
        }
        int tailBits = bits % 8;
        if (byteShift > 0 || tailBits == 0) {
            vec[i] = (vec[i] >> bitShift) | carry;
        }
        else {
            vec[i] = vec[i] >> bitShift;
            vec[i] = carry | (vec[i] << (8 - tailBits));
            vec[i] = vec[i] >> (8 - tailBits);
        }
    }
}
int main()
{
    //normal shift
    //char str[] = "11110000";
    //char str[] = "08283490jfij4r891092491243";
    //char str[] = "87123908jc1309123=cx1zk121s12312392834ucu0j3134u1092cu4j3c8u124cu9ghfugoiug8urg8egaerg";
    //char str[] = "11111111111111111111000000000000000000000000000";
    //char str[] = "1010001111110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    //char str[] = "11110000";
    char str[] = "111100011011";
    int cells = 0;
    int bits = strlen(str);
    unsigned char* vec = convertStrToLongBV(str, &cells);
    printf("Original: ");
    printBV(vec, cells);

    int k = 2;

    shiftRight(vec, bits, k);
    //shift >= bits
    //shiftRight(vec, bits, bits + 100);
    printf("Shifted : ");
    printBV(vec, cells);
    return 0;
}
