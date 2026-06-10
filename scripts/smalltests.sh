#!/bin/bash

cd ..
OUT="results/processor_distribution.csv"
echo "min max n p tmax" > "$OUT"

result=$(mpirun ---bind-to cores -np 8 --ntasks-per-node=4 ./main 1000032)

