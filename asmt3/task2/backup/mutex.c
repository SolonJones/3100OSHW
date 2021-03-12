/* this is the structure for mutex locked multi thread process*/

#include<stdlib.h>
#include<stdbool.h>

/* global lock */

bool ava = true; 

void acquire(){

	while(!ava);
	ava = false;
}

void release(){
	ava = true;
}

int main(){
	//do {
		acquire();
		// do the work inside critical section
		release();
		// everything else outside the critical section
	//}while(true);
	return 0;
}
