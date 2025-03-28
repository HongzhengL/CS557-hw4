#!/bin/bash

mkdir -p result/16_threads
mkdir -p result/1_thread

# Run with 16 threads
export OMP_NUM_THREADS=16
export MKL_NUM_THREADS=16
echo "Running with 16 threads..."
for exe in build/main_*; do
    echo "Running $exe..."
    "$exe" | tee "result/16_threads/$(basename "$exe").txt"
    echo "---------------------------------------------"
done

# Run with 1 thread
export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
echo "Running with 1 thread..."
for exe in build/main_*; do
    echo "Running $exe..."
    "$exe" | tee "result/1_thread/$(basename "$exe").txt"
    echo "---------------------------------------------"
done
