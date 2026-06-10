#!/bin/bash

cd ..
OUT="results/processor_distribution.csv"
echo "min max t25 t50 t75 t100 tmax n p" > "$OUT"

result=$(mpirun ---bind-to cores -np 8 --ntasks-per-node=4 ./main 1000032)

