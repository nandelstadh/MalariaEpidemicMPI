#!/bin/bash

cd ..
OUT="results/demonstration.csv"
echo "min max n p tmax" > "$OUT"

N=(1000000 2000000 4000000)

for i in "${!N[@]}"; do
        result=$(mpirun --bind-to cores -np 32 ./main "${N[i]}" 0)
        echo "$result" >> "$OUT"
done

