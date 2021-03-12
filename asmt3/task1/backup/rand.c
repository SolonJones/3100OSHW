
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
/* generate random # between 0~1 */

/* global var */
int circle_count;

/*
void* runner(void* param){
	int value = atoi(param);
	printf("successfully called runner with param = %d\n",value);
	int x, y; 
	x = random_double() * 2.0 -1.0;
	y = random_double() * 2.0 -1.0;
	printf("(x, y)  = ( %d, %d) \n",x, y);

}
*/

int main(int argc, char * argv[]){
  	time_t sec;	
	srandom((unsigned)time(&sec));	
	printf("\trtime() generate: %ld\n", sec);
	int ret = random() ;
	
		// ((double)RAND_MAX  + 1);
	printf("\trandom() generate: %d\n", ret);
	printf("\t RAND_MAX  generate: %d\n", RAND_MAX);
	printf("\t final / generate: %f\n", ret/(double)RAND_MAX);

	return 0;
}
