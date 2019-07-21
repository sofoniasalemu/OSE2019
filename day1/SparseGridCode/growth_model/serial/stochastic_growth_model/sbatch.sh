#!/bin/bash -l
#SBATCH --ntasks=1
#SBATCH --output=ex2.out
#SBATCH --error=ex2.err
#SBATCH --partition=broadwl
module load python
python ex2.py
