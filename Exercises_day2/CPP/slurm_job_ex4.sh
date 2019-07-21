#!/bin/bash -l
#BATCH --job-name ex4
#SBATCH --ntasks=1
#SBATCH --partition=broadwl
#SBATCH --output=ex4.out
#SBATCH --error=ex4.err
./ex4.exec
~
