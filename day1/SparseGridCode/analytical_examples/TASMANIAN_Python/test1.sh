#!/bin/bash -l
#SBATCH --ntasks=1
#SBATCH --output=ex1.out
#SBATCH --error=ex1.err
#SBATCH --partition=broadwl
#SBATCH --job-name=test
module load python
python ex1.py
