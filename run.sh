#!/bin/bash

mkdir -p result/16_threads
mkdir -p result/1_thread

export OMP_NUM_THREADS=16
export MKL_NUM_THREADS=16
for exe in build/main_*; do
    suffix=$(basename "$exe" | cut -d'_' -f2-3 | tr '\n' '_')

    echo "Running $exe..."

    "$exe" | tee "result/16_threads/main_${suffix}.txt"
done

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
for exe in build/main_*; do
    suffix=$(basename "$exe" | cut -d'_' -f2-3 | tr '\n' '_')

    echo "Running $exe..."

    "$exe" | tee "result/1_thread/main_${suffix}.txt"
done
