#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>
#include <vector>
const int niter=10; 
int main(void)
{
    int count=0;
    double z;
    double pi;
    int num_threads =1;// omp_get_max_threads();
    std::cout << "Number of threads: "<< num_threads << std::endl;
    double time = -omp_get_wtime();
    //srand(time(NULL));
    //main loop
    #pragma omp parallel for reduction(+:count)
    for (int i=0; i<niter; ++i){
        //get random points
        double x = (double)random()/RAND_MAX;
        double y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
        //check to see if point is in unit circle
       	if (z<=1)
        {
 	       count+=1;
        }
    }
    pi = ((double)count/(double)niter)*4.0;          //p = 4(m/n)
    //printf("Pi: %f\n", pi);
    time += omp_get_wtime();
    std::cout << "that took "<< time << "seconds"<<std::endl;
}

