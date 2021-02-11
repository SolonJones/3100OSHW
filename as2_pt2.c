
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
// task2 using system() call fire pt1  
// use system() to fire ps -l
// repeat 3 time for before the zomebie 
// after the zombify  
// after the wait() 


int main(){
    char cmd[30]; 
    // if the part1 changed name, you need to change this one too. 
    int id = fork();
    switch(id){
        case -1: perror(""); 
                 return 1;
        case 0: // child stuff exec()
                 execl("./a.out",NULL);
                 break ;
        default:
                 sleep(2);
                 strcpy(cmd, "ps -l");
                 system(cmd);
                 sleep(2); 
                 // force mother to sleep so that next  cmd is after the parents take first wake up
//                 system(cmd);
                 sleep(20); 
                 int status;
                 wait(&status);
                 system(cmd);
                 // another 10 secs sleep to make sure parents taken care of wait 
                 sleep(2);
                 printf("both assg1 program are now done");
                 system(cmd);
    }
}
