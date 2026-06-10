#!/bin/bash

cd ..
OUT="results/processor_distribution.csv"

result=$(mpirun ---bind-to cores -np 8 --ntasks-per-node=4 ./main 1000032 1)
echo "$result" >> "$OUT"

