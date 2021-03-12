
#!/bin/bash
# this is the bash script to complie and run the test with pre-prepared input file 

# file name 
file_name="task1.c"

# compile the file 
gcc -pthread $file_name -lm

if [[ $? == 0 ]]; then 
	./a.out 100 >> log_task1.txt ;
	./a.out 1000 >> log_task1.txt ;
	./a.out 10000 >> log_task1.txt ;
	./a.out 100000 >> log_task1.txt ;
fi 

echo "successfully complete test and generated log file"


