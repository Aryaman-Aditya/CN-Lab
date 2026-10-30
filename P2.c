#include<stdio.h>
#include<stdlib.h>
struct student_info{
    int roll;
    char name[50];
    float CGPA;
    int age ;
};

void f1(struct student_info s1 ){
    printf("roll: %d \n", s1.roll);
    printf("name: %s \n", s1.name);
    printf("CGPA: %f \n", s1.CGPA);
    printf("age: %d \n", s1.age);
}

void f2(struct student_info *s2){
    printf("roll : %d\n", s2->roll);
    printf("name: %s \n", s2->name);
    printf("CGPA: %f \n", s2->CGPA);
    printf("age: %d \n", s2->age);
}

int main(int argc, char* argv[]){
    struct student_info s1 = {24155166, "Aryaman", 9.1, 20};
    printf("Used call by value:\n");
    f1(s1);

    printf("call by address:\n");
    f2(&s1);


    return 0;
}