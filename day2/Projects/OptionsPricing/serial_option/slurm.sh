#!/bin/bash -l
#SBATCH --ntasks=1
#SBATCH --output=option.out
#SBATCH --error=option.err
#SBATCH --partition=broadwl
#SBATCH --job-name=option
g++ european_asian_option.cpp -o european_asian_option.exec
./european_asian_option.exec
