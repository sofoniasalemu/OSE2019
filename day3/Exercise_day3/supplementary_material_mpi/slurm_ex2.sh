#!/bin/bash
#SBATCH --job-name=ex2
#SBATCH --output=ex2.out
#SBATCH --error=ex2.err
#SBATCH --ntasks=4
#SBATCH --partition=broadwl

module load openmpi

mpirun ./allreduce.exec
~
