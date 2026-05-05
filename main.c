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
        if (byteShift > 0) {
            vec[i] = (vec[i] >> bitShift) | carry;
        }
        else {
            int tailBits = bits % 8;
            vec[i] = vec[i] >> bitShift;
            vec[i] = carry | (vec[i] << (8 - tailBits));
            vec[i] = vec[i] >> (8 - tailBits);
        }
    }
}
int main()
{
    return 0;
}
