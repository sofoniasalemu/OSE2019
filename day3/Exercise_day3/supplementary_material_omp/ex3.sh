#!/bin/bash -l
#SBATCH --error=ex3.err
#SBATCH --output=ex3.out
#SBATCH --partition=broadwl
g++ paral_pi.cpp -fopenmp -o  paral_pi.exec
export OMP_NUM_THREADS=1
./paral_pi.exec
export OMP_NUM_THREADS=8
./paral_pi.exec
export OMP_NUM_THREADS=16
./paral_pi.exec
