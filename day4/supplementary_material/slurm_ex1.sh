#!/bin/bash
#SBATCH --ntasks=4
#SBATCH --error=ex1.err
#SBATCH --output=ex1.out
#SBATCH --partition=broadwl

module load openmpi
export OMP_NUM_THREADS=8

mpirun ./pi_openmp_parallel.exec
