#include <stdio.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include <stdlib.h>
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
int main(int argc, char *argv[]) {


	//Variables
	double sum;
	int i, n = 30000;
	struct  timespec  start,  end;
	int size,rank;


	//Code
	sum = 0;


	//MPI INIT
	int rc = MPI_Init(&argc,&argv);
	if(rc != MPI_SUCCESS){
		 MPI_Abort(MPI_COMM_WORLD,3);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0){
		printf("Number of processes(size): %d \n",size);
	}


	//"Division of Labor"
	int work1 = (n + 1) / size; //Division of work among CPUs (work per proc)
	int work2 = ((n+1) % size); //Rest of the work
	int start_step = rank*work1 + MIN(rank,work2); //Itteration starting point (MIN is defined)
	int end_step = start_step+work1-1; // Itteration stoping point
	if (work2>rank)end_step=end_step+1;//

	if(rank == 0){
		clock_gettime(CLOCK_MONOTONIC,  &start); //Start  clock
	}


	for (i = start_step; i <= end_step; i++){
		sum += f(i);
	}



	//Reducted sum
	double redsum=0;
	MPI_Reduce(&sum,&redsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);



	if (rank == 0 ){
		clock_gettime(CLOCK_MONOTONIC, &end);//Stop clock

		printf("The sum is %.2f\n", redsum);

		const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
		long timeElapsed_s = end.tv_sec - start.tv_sec;
		long timeElapsed_n = end.tv_nsec - start.tv_nsec;
		//If we have a negative number in timeElapsed_n , borrow a carry from seconds
		if ( timeElapsed_n < 0 ) {
			timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;
			timeElapsed_s--;
		}

	 	printf("Time elapsed : %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);

	}




MPI_Finalize();
return 0;
}
