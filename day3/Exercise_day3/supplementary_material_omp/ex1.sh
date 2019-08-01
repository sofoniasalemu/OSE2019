#!/bin/bash 
#SBATCH --error=ex1.err
#SBATCH --output=ex1.out
#SBATCH --partition=broadwl
#SBATCH --ntasks=1
module load openmpi/3.1.2

#SBATCH --cpu-per-task=8
export OMP_NUM_THREADS=8
##g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec
./normalize_vec.exec

#SBATCH --cpu-per-task=16
export OMP_NUM_THREADS=16
##g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec
./normalize_vec.exec

#SBATCH --cpu-per-task=32
export OMP_NUM_THREADS=32
##g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec
./normalize_vec.exec

