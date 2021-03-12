#!/bin/bash
# this is the bash script to complie and run the test with pre-prepared input file 

# file name 
file_name="task2.c"

# compile the file 
gcc -pthread $file_name -lm

if [[ $? == 0 ]]; then 
	./a.out 1000000 2 >> log_task2.txt ;
	./a.out 1000000 20 >> log_task2.txt ;
	./a.out 1000000 40 >> log_task2.txt ;
	./a.out 1000000 80 >> log_task2.txt ;
	./a.out 1000000 100 >> log_task2.txt
fi 


