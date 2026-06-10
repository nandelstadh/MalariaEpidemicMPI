#!/bin/bash

cd ..
OUT="results/processor_distribution.csv"

result=$(mpirun --bind-to cores -np 8 --map-by ppr:4:node ./main 1000032 1)
echo "$result" >> "$OUT"

