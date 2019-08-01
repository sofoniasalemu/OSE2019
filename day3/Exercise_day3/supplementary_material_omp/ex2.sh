#!/bin/bash -l
#SBATCH --error=ex2.err
#SBATCH --output=ex2.out
#SBATCH --partition=broadwl
##g++ dot_prod.cpp -fopenmp -o dot_prod.exec
export OMP_NUM_THREADS=1
./dot_prod.exec
export OMP_NUM_THREADS=2
./dot_prod.exec
export OMP_NUM_THREADS=3
./dot_prod.exec
export OMP_NUM_THREADS=4
./dot_prod.exec
export OMP_NUM_THREADS=5
./dot_prod.exec
export OMP_NUM_THREADS=6
./dot_prod.exec
export OMP_NUM_THREADS=7
./dot_prod.exec
export OMP_NUM_THREADS=8
./dot_prod.exec
