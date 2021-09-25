#include <stdio.h>
#include <math.h>
#include <time.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
//--------------IMPORTANT NOTE-----------------//
// MUST BE COMPILED WITH "-lm"
//---------------------------------------------//

//Function calculates sin sums.
double f(int i) {
	int j, start = i * (i + 1) / 2, finish = start + i;
	double return_val = 0;
	for (j = start; j < finish; j++)
	return_val += sin(j);
	return return_val;
}


//Main function calculating the sum. 
int main() {


	//Variables
	double sum;
	int i, n = 30000;
	struct  timespec  start,  end;

	//Code
	sum = 0;

	clock_gettime(CLOCK_MONOTONIC,  &start); //Start  clock

	for (i = 0; i <= n; i++){
		sum += f(i);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);//Stop clock

	printf("The sum is %.2f\n", sum);


	const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
	long timeElapsed_s = end.tv_sec - start.tv_sec;
	long timeElapsed_n = end.tv_nsec - start.tv_nsec;
	//If we have a negative number in timeElapsed_n , borrow a carry from seconds
	if ( timeElapsed_n < 0 ) {
		timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;
		timeElapsed_s--;
	}



 	printf("Time elapsed : %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);



return 0;
}
