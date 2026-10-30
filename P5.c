#include <stdio.h>

int isLittleEndian() {
    unsigned int x = 1;
    char *c = (char *)&x;
    return (*c == 1);  // 1 => little endian, 0 => big endian
}

unsigned int swapEndian(unsigned int num) {
    return ((num >> 24) & 0x000000FF) |
           ((num >> 8)  & 0x0000FF00) |
           ((num << 8)  & 0x00FF0000) |
           ((num << 24) & 0xFF000000);
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    if (isLittleEndian())
        printf("Host machine is Little Endian\n");
    else
        printf("Host machine is Big Endian\n");

    unsigned char *bytePtr = (unsigned char *)&num;
    printf("Byte layout in memory (as stored): ");
    for (int i = 0; i < 4; i++)
        printf("%02X ", bytePtr[i]);
    printf("\n");

    unsigned int converted = swapEndian(num);
    printf("Original number: %u\n", num);
    printf("Endian-swapped number: %u\n", converted);

    return 0;
}