#!/bin/bash -l
#SBATCH --error=ex1.err
#SBATCH --output=ex1.out
#SBATHC --partition=broadwl
g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec
export OMP_NUM_THREADS=8
./normalize_vec.exec
export OMP_NUM_THREADS=16
./normalize_vec.exec
export OMP_NUM_THREADS=32
./normalize_vec.exec

