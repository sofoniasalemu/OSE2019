#!/bin/bash
#SBATCH --job-name=ex1
#SBATCH --output=ex1.out
#SBATCH --error=ex1.err
#SBATCH --ntasks=4
#SBATCH --partition=broadwl

module load openmpi

mpirun ./broadcast.exec
