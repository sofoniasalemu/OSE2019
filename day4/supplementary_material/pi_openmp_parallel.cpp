#include <iostream>
#include <cmath>
#include <mpi.h>
#include <omp.h>

#define _USE_MATH_DEFINES

const int num_steps = 500000000;
int main(int argc, char *argv[]){
    int numprocs, rank;

    int i;
    double pi  = 0.0;
    double pi_tot=0.0;
    double x;
    std::cout << "using " << omp_get_max_threads() << " OpenMP threads" << std::endl;

    const double w = 1.0/double(num_steps);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double time = -omp_get_wtime();
    double sum =0.0;

    #pragma omp parallel for shared(rank,numprocs), private(i,x) , reduction(+:sum)
    for(i=rank; i<=num_steps; i=i+numprocs) {
        x = ((double)i+0.5)*w;
        sum += 4.0/(1.0+x*x);
    }

    pi = sum*w;

    MPI_Reduce(&pi,&pi_tot,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    
    time += omp_get_wtime();
    if (rank==0){
    std::cout << num_steps
              << " steps approximates pi as : "
              << pi_tot
              << ", with relative error "
              << std::fabs(M_PI-pi_tot)/M_PI
              << std::endl;
    std::cout << "the solution took " << time << " seconds" <<std::endl;
    }
    MPI_Finalize();
}
