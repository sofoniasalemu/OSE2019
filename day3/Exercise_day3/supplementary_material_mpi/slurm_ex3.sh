#!/bin/bash
#SBATCH --job-name=ex3
#SBATCH --output=ex3.out
#SBATCH --error=ex3.err
#SBATCH --ntasks=4
#SBATCH --partition=broadwl

module load openmpi

mpirun ./scatter.exec

