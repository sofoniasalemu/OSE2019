#!/bin/bash -l
#SBATCH --error=ex5.err
#SBATCH --output=ex5.out
#SBATCH --partition=broadwl
module load openmpi
##g++ eu_as.cpp -fopenmp -o eu_as.exec
export OMP_NUM_THREADS=8
./eu_as.exec
export OMP_NUM_THREADS=16
./eu_as.exec
export OMP_NUM_THREADS=24
./eu_as.exec
~
