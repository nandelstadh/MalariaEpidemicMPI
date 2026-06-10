#!/bin/bash
#SBATCH -A uppmax2026-1-31
#SBATCH -N 2
#SBATCH --exclusive
#SBATCH --time=00:10:00

./smalltests.sh
