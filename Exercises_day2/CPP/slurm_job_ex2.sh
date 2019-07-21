#!/bin/bash
#SBATCH --job-name ex2
#SBATCH --ntasks=1
#SBATCH --partition=broadwl
#SBATCH --output=ex2.out
#SBATCH --error=ex2.err
./hidiho.exec
