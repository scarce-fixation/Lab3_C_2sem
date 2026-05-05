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
    vec[cells - 1] >>= (8 - tailBits);
}
int main()
{
    return 0;
}
