#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    unsigned int num;
    struct pkt p;

    printf("Enter a 4-byte number: ");
    scanf("%u", &num);

    p.ch1    = num & 0xFF;
    p.ch2[0] = (num >> 8) & 0xFF;
    p.ch2[1] = (num >> 16) & 0xFF;
    p.ch3    = (num >> 24) & 0xFF;

    printf("ch1: %d\n", (unsigned char)p.ch1);
    printf("ch2[0]: %d\n", (unsigned char)p.ch2[0]);
    printf("ch2[1]: %d\n", (unsigned char)p.ch2[1]);
    printf("ch3: %d\n", (unsigned char)p.ch3);

    unsigned int reconstructed =
        ((unsigned char)p.ch1) |
        ((unsigned char)p.ch2[0] << 8) |
        ((unsigned char)p.ch2[1] << 16) |
        ((unsigned char)p.ch3 << 24);

    printf("Reconstructed number: %u\n", reconstructed);
    return 0;
}