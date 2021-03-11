#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
// task1 using system call to fork a child  done 
// turn the child into a zombie for at least 10 sec 
// use ps -l to check if the task is complete

int main(){
    char cmd[30];
    int child = fork();
    if(child==-1){
        perror("failed fork");
        exit(300);
    }
    else if(child ==0){
        //child stuff
        sleep(1);
        printf("the child %d has been forked\n", getpid());
        printf("the child %d became zombie now \n", getpid());
        exit(1);
    }
    else
    {
        //parents  stuff 
        int status;
        sleep(10);
        printf("the parent %d is alive but child is now zombie \n", getpid());
        sleep(10);
        if(child !=wait(&status)){
            perror("wait err, fatal");
            exit(77);
        }
        printf("the parent %d take care of zombie %d\n", getpid(), child);
    }
}
