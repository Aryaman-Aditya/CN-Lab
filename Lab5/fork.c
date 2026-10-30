#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
//simple fork 
int main(){
    int pid = fork();// pid=0 is child. else parent
    if(pid == 0){
        printf("Child process id: %d\n", getpid());
        printf("Childs parent id: %d\n\n", getppid());

    }
    else if(pid > 0){
        printf("Parent process id: %d\n", getpid());
    }
}
//Handling multiplie clients is possible with fork() or IO multiplexing.
//Server is parent process. Clients are child processes.