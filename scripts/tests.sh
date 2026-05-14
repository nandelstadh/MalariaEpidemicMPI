#!/bin/bash

cd ..
OUT="results/weak_scale.csv"
echo "min max t25 t50 t75 t100 tmax n p" > "$OUT"

N=(100000 200000 400000 800000 1600000 3200000 4800000)
P=(1 2 4 8 16 32 48)

for i in "${!N[@]}"; do
        result=$(mpirun --bind-to cores -np "${P[i]}" ./main "${N[i]}")
        echo "$result" >> "$OUT"
done

OUT="results/strong_scale.csv"
echo "min max t25 t50 t75 t100 tmax n p" > "$OUT"

P=(1 2 4 8 16 32 48)

for p in "${P[@]}"; do
        result=$(mpirun --bind-to cores -np "$p" ./main 1000032)
        echo "$result" >> "$OUT"
done
