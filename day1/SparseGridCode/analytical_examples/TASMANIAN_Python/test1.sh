#!/bin/bash -l
#SBATCH --ntasks=1
#SBATCH --output=test.out
#SBATCH --error=test.err
#SBATCH --partition=broadwl
#SBATCH --job-name=test
module load python/3.7.0
python OSE_example.py
