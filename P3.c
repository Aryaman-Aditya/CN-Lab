//Extracting each byte from a number and storing them in seaparate char variables
#include<stdio.h>
#include<stdlib.h>

int main(){
    int i = 0x66332288;

    unsigned char* p = (unsigned char *)&i; 
    //unsigned used to neglect -ve values since address cant be -ve
    //char pointer points to 1 byte only, int pointer pojtns to 4 bytes at once.
    printf("%x\n", p[0]);
    printf("%x\n", p[1]);
    printf("%x\n", p[2]);
    printf("%x\n", p[3]);
    return 0;
}