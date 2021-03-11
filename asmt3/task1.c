#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


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


/* generate random # between 0~1 */
double random_double(){
	return random() / ((double)RAND_MAX  + 1);
}

/* global var */
int circle_count, total_count;

int main(){
	
	/* seed random() */
	srandom();	

	int x, y, hit_count; 

	/* generate x y pairs, adjusted */ 
	/* adjustment assume orig at left-low corner of square */
	x = random_double() * 2.0 -1.0;
	y = random_double() * 2.0 -1.0;
	/* test if sqaure root of (x^2 + y^2) is within circle */
	if(sqrt(x*x +y*y) < 1.0)
		++hit_count;	

	printf(%s,%d ,%d, %s, %d, " the x y coordinate is ", x, y, " within the circle", hit_count);		

	/* calcualte pi by master thread */
	{
	
	}
	return 0;
}
