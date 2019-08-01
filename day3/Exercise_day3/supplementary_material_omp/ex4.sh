#!/bin/bash -l
#SBATCH --error=ex4.err
#SBATCH --output=ex4.out
#SBATCH --partition=broadwl
module load openmpi
g++ BS_paral.cpp -fopenmp -o BS_paral.exec
export OMP_NUM_THREADS=8
./BS_paral.exec
export OMP_NUM_THREADS=16
./BS_paral.exec
export OMP_NUM_THREADS=24
./BS_paral.exec
