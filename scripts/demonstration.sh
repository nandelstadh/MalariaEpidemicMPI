#!/bin/bash

cd ..
OUT="results/demonstration.csv"
echo "min max t25 t50 t75 t100 tmax N p" > "$OUT"

N=(1000000 2000000 4000000)

for i in "${!N[@]}"; do
        result=$(mpirun --bind-to cores -np 32 ./main "${N[i]}")
        echo "$result" >> "$OUT"
done

