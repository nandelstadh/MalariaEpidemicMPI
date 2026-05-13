#!/bin/bash
#SBATCH -A uppmax2026-1-92
#SBATCH -n 32
#SBATCH -N 1
#SBATCH --time=00:10:00
module load OpenMPI/matplotlib

./tests.sh
