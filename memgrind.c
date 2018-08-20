#include <stdlib.h>
#include "mymalloc.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

unsigned int
randomr(unsigned int min, unsigned int max)
{
       double x= (double)rand()/RAND_MAX;

       return (max - min +1)*x+ min;
}

int main(){

	

	//TEST CASE A
	//create var to store average and reset time taken
	double avg=0;
	double time_taken=0;
	//create a clock for test 2 
	clock_t two;	
	// run test
	int i;
	for(i=0; i<150; i++){
		two = clock();
		time_taken=0;
		//init_heap();
		char* ptr = mymalloc(1,__FILE__,__LINE__);
		myfree(ptr,__FILE__,__LINE__);
		two = clock() - two;
		time_taken = ((double)two)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}

	//print out the average runtime for test 2
	printf("Test Case B: %f\n", avg/150);
	

	//TEST CASE B
	//create char array to store all the different malloced nodes
	char* arr[1000];
	//create clock to run test
	clock_t one;
	//start clock
	one = clock();

	//run test
	for(i=0; i<150; i++){
		arr[i] = mymalloc(1,__FILE__,__LINE__);		
	}

	for(i=0; i<150; i++){
		myfree(arr[i],__FILE__,__LINE__);
	}
	//get total time
	one = clock() - one;
	//convert to double
	time_taken = ((double)one)/CLOCKS_PER_SEC;
	
	//print resulting time
	printf("Test Case A: %f\n", time_taken);



	//TEST CASE C
	//reset the avg var and time_take from previous test
	avg=0;
	time_taken=0;
	//create clock for test 3
	clock_t three;
	int* ptr;
	//run test
	for(i=0;i<150; i++){
		time_taken=0;
		//init_heap();
		three = clock();
		srand(time(NULL));
		int r = rand();
		
		if(r%2==0){
			ptr = (int*)mymalloc(1,__FILE__,__LINE__);	
		}
		else if(r%3==0){
			myfree(ptr,__FILE__,__LINE__);
		}
	
		three = clock()-three;
		time_taken = ((double)three)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}
	//print the avg time
	printf("Test Case C: %f\n", avg/100);
	
	//TEST CASE D
	//create a clock for test 4 and reset timinig variables
	clock_t four;
	time_taken=0;
	avg=0;
	char* ptr_arr[150];
	int j = 0; 
	//rn the random test for test 4
	for(i=0; i<150; i++){

		time_taken=0;
		four = clock();
		int r = rand();
		int x = randomr(1, 64);
		if(r%3==0){
			ptr_arr[j]= (char*)mymalloc(x,__FILE__,__LINE__);
			j++;

		}
		else if(r%2==0){
			myfree(ptr_arr[j],__FILE__,__LINE__);
			if(j>0)			
				j--;
		}
		four = clock()-four;
		time_taken = ((double)four)/CLOCKS_PER_SEC;
		avg+=time_taken;		
	}

	for(i=0; i<j; i++){
		free(ptr_arr[i]);
	}
	//print the result
	printf("Test Case D: %f\n", avg/150);

	
	//TEST CASE E
	//create a clock, reset timing variables
	clock_t five;
	time_taken=0;
	avg=0;

	//run test
	for(i=0; i<100; i++){
		time_taken=0;
		five = clock();
		//init_heap();		
	
		int* ptr = (int*)mymalloc(20,__FILE__,__LINE__);
		int* ptr2 = (int*)mymalloc(20,__FILE__,__LINE__);
		int* ptr3 = (int*)mymalloc(1000,__FILE__,__LINE__);
		myfree(ptr3,__FILE__,__LINE__);
		myfree(ptr,__FILE__,__LINE__);	
		myfree(ptr2,__FILE__,__LINE__);	

		five = clock() - five;
		time_taken = ((double)five)/CLOCKS_PER_SEC;
		avg+=five;
	}
	//print out the avg
	printf("Test Case E: %f\n", avg/100);



	//TEST CASE F
	//reset timing variables and create a clock for test 6
	clock_t six;
	time_taken=0;
	avg=0;

	//run test
	for(i=0; i<100; i++){
		time_taken=0;
		six = clock();		
		//init_heap();
		int* ptr = (int*)mymalloc(20,__FILE__,__LINE__);
		int* ptr2 = (int*)mymalloc(20,__FILE__,__LINE__);
		
		myfree(ptr2,__FILE__,__LINE__);
		myfree(ptr,__FILE__,__LINE__);
		six = clock() - six;
		time_taken = ((double)five)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}	
	//print avg
	printf("Test Case F: %f\n", avg/100);
}
