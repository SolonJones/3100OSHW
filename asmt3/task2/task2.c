#include<stdbool.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<sys/time.h>
#define MAX 5000
/***gnereal description of probelm***
 * construct a square and a circle within the square 
 * given square length of 2, circle radias of 1 
 * generate a random number p(x,y) which must be within the square
 * count the # of p which resides within the circle 
 * estimate pi=4 * (# of p in circle) / (total # of p) 
 */

/***code specific requirement***
 * this piece of code contains one master thread 
 * user specify how many random with be generated
 * user specify how many thread will be created 
 * divide work amount thread 
 * each thread modify hit_count 
 * each thread must protect agianst race using mutex 
 * 
 */ 

/* global var */
int hit_count;
bool ava = true;

/* declear itoa for linker to loock up */
char * itoa(int, char*, int);

/* mutex locks*/
void acquire(){
	while(!ava);
	ava=false;
}

void release(){
	ava =true;
}
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


/* thread */
void* runner(void* param){
//	printf("%s","created new thread! ");
	int value = atoi(param);
	int hit_count_local = 0;
//	printf("successfully called runner with param = %d\n",value);
	double x, y; 
	/* generate x y pairs, adjusted */ 
	/* adjustment assume orig at left-low corner of square */
	
	for(int i=0; i< value;i++){
			//printf("local old hit_count = %d\n",hit_count);
		x = random_double() * 2.0 -1.0;
		y = random_double() * 2.0 -1.0;
//		printf("(%f,%f)",x, y);
		/* test if sqaure root of (x^2 + y^2) is within circle */
		if(sqrt(x*x +y*y) < 1.0)
			++hit_count_local;	
	}
//	printf("total hit_count = %d\n",hit_count);
//	printf("total round = %d\n",value);
	
	acquire();
	hit_count += hit_count_local;
	release();
	pthread_exit(0);
}


int main(int argc, char * argv[]){
	/* call timeval to measure start point*/
	struct timeval st, ed;
	gettimeofday(&st,NULL);

//	printf("start time %ld \n", st);
	/* read input from user for total_count*/
	if ( argc !=3){
		exit(3);
	}
	int total_count = atoi(argv[1]) ;	
	int thread_num = atoi(argv[2]);
	int count_per_thread = total_count/thread_num;
	char str[MAX];

	//itoa(count_per_thread, str, 10);
	sprintf(str,"%d", count_per_thread);

	srandom((unsigned)time(NULL));	
	/* call thread with this toutal count */

	/*1. create threads */ 
	pthread_t tids[thread_num];
	pthread_attr_t attrs[thread_num];
	for(int i=0; i< thread_num; i++){
		pthread_attr_init(attrs+i);
		pthread_create(tids+i, attrs+i, runner, (void*)str);
		pthread_join(tids[i],NULL);
	}


	/* thread exit, master calcualte pi by useing total count and hit count */
	{
		double pi = (double)4*(hit_count)/total_count;

		gettimeofday(&ed,NULL);
		//	printf("end time %ld \n", ed);
		unsigned long delta_t = ed.tv_usec -st.tv_usec;
		printf("\n\tpi=%f\tthread_num=%d\truning time =%lu micro_secs\n\n\n",pi,thread_num, delta_t);
	}
	return 0;
}
