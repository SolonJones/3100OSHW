1. Run exe.sh by typing ./exe.sh
2. view log file for output 
3. run exe.sh again will append result to the log file 

if the exe.sh failed to complie 
1. complie the taskX.c file by hand using: 
	gcc -pthread taskX.c -lm
2. if it is task 1 run the file with: 
	./a.out 100 
	./a.out 1000 
	./a.out 10000 
	...etc... 
3. if it is task 2 run the ps with: 
	./a.out 1000000 2 
	./a.out 1000000 20 
	./a.out 1000000 40 
	...etc... 


0. All the debug code is in the dir named backup which should not be concerned by the graders. 
