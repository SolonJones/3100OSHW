#include<sys/stat.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define SIZE 1024 
#define db 0

int main(int argc, char* argv[]){

	// check if 2 cmd args were provided, quit if not 
	if(argc < 3){
		perror("invalid arguements, exiting");
		exit(0);
	}	
	int fd1, fd2; 

	// open file by arg1 
	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1){
		// error for invalid input file name
		perror("invalid input file path, exiting");
		exit(0);
	}
	// check if arg2 path already exist 
	if(access(argv[2],F_OK)==0){
		perror("output file exist, exiting");
		exit(0);
	}
	// open file by arg2 
	fd2 = open(argv[2], O_CREAT | O_WRONLY,S_IRWXU);
	if(fd2 == -1){
		// error for invalid output file name
		perror("invalid output file path, exiting");
		exit(0);
	}	

	// read into buffer from fd1 
	char buf[SIZE];
	int readN, writeN;
	// if read success 
	while((readN = read(fd1, buf, SIZE))>0){
		if(db){
		printf("readN is %d\n",readN);
		}
		// write bit stream from fd1 to fd2 
		writeN = write(fd2, buf, readN);
		if(db){
		printf("writeN is %d\n",writeN);
		}

		// unable to write
		if(writeN ==-1){
			perror("writef failed, crashing");
			exit(1);
		}
		// paritla write 
		if(writeN != readN){
			perror("partial write, crashing");
			exit(1);
		}
	}
	//if read fial 
	if(readN ==-1){
		perror("read failed, crashing");
		exit(1);
	}
	// closeing fd 1 and 2 
	if(close(fd1)==-1){
		perror("close fd1 failed, crashing");
		exit(1);

	}

	if(close(fd2)==-1){
		perror("close fd2 failed, crashing");
		exit(1);
	}

	printf("operation complete, total read/write %d bytes", writeN);
	exit(0);
}
