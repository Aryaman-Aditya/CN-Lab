//Command line argument 
#include<stdio.h>
#include<stdlib.h>
void swap( int *x , int *y){
    int temp =*x;
    *x = *y;
    *y = temp;
}
int main(int argc, char *argv[]){ // argc: counts number of arguments
    //argv: Character pointer array keeping location of each argument
    if(argc !=3){
        printf("Usage: %s num1 num2 \n", argv[0]);
        return 1;

    }

    //atoi: Convert ASCII to integer, itoa: Convert int to ASCII
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    //Since argv is char array, the integer given by command line needs to be converted to integer using atoi
    printf("Before swap : a= %d, b= %d \n\t",a,b);
    swap(&a,&b);
    printf("After swap: a= %d , b= %d \n",a,b);

    return 0;
}