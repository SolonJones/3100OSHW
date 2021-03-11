#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

/***gnereal description of probelm***
 * construct a square and a circle within the square 
 * given square length of 2, circle radias of 1 
 * generate a random number p(x,y) which must be within the square
 * count the # of p which resides within the circle 
 * estimate pi=4 * (# of p in circle) / (total # of p) 
 */

/***code specific requirement***
 * this piece of code contains one master thread 
 * one slave thread 
 */ 

int hit_count;

/* generate random # between 0~1 */
double random_double(){
	/* seed random() */
	srandom((unsigned)time(NULL));	

	int ret = random() / ((double)RAND_MAX  + 1);
	printf("\trandom() generate: %d\n", ret);
	return ret;
}


void generate_test(){


}
/* global var */
int circle_count;


/* thread */
void* runner(void* param){
	int value = atoi(param);
	printf("successfully called runner with param = %d\n",value);
	int x, y; 
	/* generate x y pairs, adjusted */ 
	/* adjustment assume orig at left-low corner of square */

	printf("old hit_count = %d\n",hit_count);
	x = random_double() * 2.0 -1.0;
	y = random_double() * 2.0 -1.0;
	/* test if sqaure root of (x^2 + y^2) is within circle */
	if(sqrt(x*x +y*y) < 1.0)
		++hit_count;	

	printf("(x, y)  = ( %d, %d) \n",x, y);
	printf("new hit_count = %d\n",hit_count);

	pthread_exit(0);
}


int main(int argc, char * argv[]){
	/* read input from user for total_count*/
	if ( argc !=2){
		exit(2);
	}
	int total_count = atoi(argv[1]) ;	

	/* call thread with this toutal count */

	/*1. create thread*/ 
	pthread_t tid ;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv[1]);
	pthread_join(tid,NULL);


	/* thread exit, master calcualte pi by useing total count and hit count */
	{

	}
	return 0;
}
