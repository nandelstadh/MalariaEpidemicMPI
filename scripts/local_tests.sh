#!/bin/bash

cd ..
OUT="results/local_weak_scale.csv"
echo "min max n p tmax" > "$OUT"

N=(100000 200000 400000 800000 1100000)
P=(1 2 4 8 11)

for i in "${!N[@]}"; do
        result=$(mpirun -np "${P[i]}" ./main "${N[i]}" 1)
        echo "$result" >> "$OUT"
done

OUT="results/local_strong_scale.csv"
echo "min max n p tmax" > "$OUT"

P=(1 2 4 8)

for p in "${P[@]}"; do
        result=$(mpirun -np "$p" ./main 800000 1)
        echo "$result" >> "$OUT"
done
