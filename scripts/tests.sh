#!/bin/bash

cd ..
OUT="results/weak_scale.csv"
echo "min max t25 t50 t75 t100 tmax N p" > "$OUT"

N=(1000000 2000000 4000000 8000000 16000000 32000000 48000000)
P=(1 2 4 8 16 32 48)

for i in "${!N[@]}"; do
        result=$(mpirun --bind-to cores -np "${P[i]}" ./main "${N[i]}")
        echo "$result" >> "$OUT"
done

OUT="results/strong_scale.csv"
echo "min max t25 t50 t75 t100 tmax N p" > "$OUT"

P=(1 2 4 8 16 32 48)

for p in "${P[@]}"; do
        result=$(mpirun --bind-to cores -np "$p" ./main 48000000)
        echo "$result" >> "$OUT"
done
