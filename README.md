# Example-of-Parallel-Computing
Small example that shows how parallel computing helps us achieve faster run time using MPI and OpenMP.
In this Reduction example we have a serial code (in C) and 3 parallel versions: 1 MPI, 1 OpenMP and a Hybrid (MPI+OpenMP).

Serial code is compiled/run as such : 
 ```
 gcc Example.c -o Example -lm
  ./Example
 ```  

MPI code :
```
 mpicc Example.c -o Example -lm 
 mpirun -n a Example.c -o Example   // Where "a" is the number of processes you would like to use
```

OMP code : 
```
gcc Example.c -o Example -lm -fopenmp
 ./Example
```

Hybrid code : 
  ```
  mpicc Example.c -o Example -lm -fopenmp
  mpirun -n a Example.c -o Example // Where "a" is the number of processes you would like to use
  ```
