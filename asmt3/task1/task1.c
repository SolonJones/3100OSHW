#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<sys/time.h>
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
	int nom = random(); 
	double den = (double)RAND_MAX  + 1;
//	printf("\t random() generate: %d\n", nom);
//	printf("\t RANDMAX generate: %f\n", den);
	double ret = (double) nom/den;
//	printf("\t ret is : %f\n", (double)nom/den);
	return ret;
}

/* global var */
int circle_count;


/* thread */
void* runner(void* param){
	int value = atoi(param);
//	printf("successfully called runner with param = %d\n",value);
	double x, y; 
	/* generate x y pairs, adjusted */ 
	/* adjustment assume orig at left-low corner of square */
	
	for(int i=0; i< value;i++){
		//	printf("old hit_count = %d\n",hit_count);
		x = random_double() * 2.0 -1.0;
		y = random_double() * 2.0 -1.0;
//		printf("(%f,%f)",x, y);
		/* test if sqaure root of (x^2 + y^2) is within circle */
		if(sqrt(x*x +y*y) < 1.0)
			++hit_count;	
	}
//	printf("total hit_count = %d\n",hit_count);
//	printf("total round = %d\n",value);

	pthread_exit(0);
}


int main(int argc, char * argv[]){
	/* call timeval to measure start point*/
	struct timeval st, ed;
	gettimeofday(&st,NULL);

//	printf("start time %ld \n", st);
	/* read input from user for total_count*/
	if ( argc !=2){
		exit(2);
	}
	int total_count = atoi(argv[1]) ;	

	srandom((unsigned)time(NULL));	
	/* call thread with this toutal count */

	/*1. create thread*/ 
	pthread_t tid ;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv[1]);
	pthread_join(tid,NULL);
	


	/* thread exit, master calcualte pi by useing total count and hit count */
	{
	double pi = (double)4*(hit_count)/total_count;
		
	gettimeofday(&ed,NULL);
//	printf("end time %ld \n", ed);
	unsigned long delta_t = ed.tv_usec -st.tv_usec;
	printf("pi = %f with runing time %lu micro_secs \n",pi, delta_t);
	}
	return 0;
}
