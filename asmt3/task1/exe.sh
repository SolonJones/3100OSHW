
#!/bin/bash
# this is the bash script to complie and run the test with pre-prepared input file 

# file name 
file_name="task1.c"

# compile the file 
gcc -pthread $file_name -lm

if [[ $? == 0 ]]; 
then 
	date >> log_task1.txt
	./a.out 100 >> log_task1.txt ;
	./a.out 1000 >> log_task1.txt ;
	./a.out 10000 >> log_task1.txt ;
	./a.out 100000 >> log_task1.txt ;
	printf "\n\n" >> log_task1.txt
	echo "successfully complete test and generated log file"
else
	echo "something went wrong, try to manually complie and run -- see README.md for details."
fi 



