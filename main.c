#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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
        int tailBits = bits % 8;
        unsigned char tail = 0;
        tail = vec[i];
        if (tailBits > 0) {
            tail = tail << (8 - tailBits);
            carry = tail >> (8 - bitShift);
            tail = tail << bitShift;
            tail = tail >> (8 - tailBits);
        }
        else {
            carry = tail >> (8 - bitShift);
            tail = tail << bitShift;
        }
        vec[i] = tail;
        i--;
        for (; i >= 0; i--) {
            unsigned char nextCarry = vec[i] >> (8 - bitShift);
            vec[i] = (vec[i] << bitShift) | carry;
            carry = nextCarry;
        }
    }
}

int main()
{
    return 0;
}
