#!/bin/bash
#SBATCH -A uppmax2026-1-31
#SBATCH -N 1
#SBATCH --exclusive
#SBATCH --time=01:00:00

./tests.sh
