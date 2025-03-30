#!/bin/bash

# Define the options
MATRIX_SIZES=(512 1024 2048 4096 8192)
BLOCK_SIZES=(16 32 64 128 256 512)

# Loop over all combinations
for MATRIX_SIZE in "${MATRIX_SIZES[@]}"; do
  for BLOCK_SIZE in "${BLOCK_SIZES[@]}"; do
    echo "Building with MATRIX_SIZE=${MATRIX_SIZE}, BLOCK_SIZE=${BLOCK_SIZE}"
    make MATRIX_SIZE=${MATRIX_SIZE} BLOCK_SIZE=${BLOCK_SIZE}
    echo "Build complete for MATRIX_SIZE=${MATRIX_SIZE}, BLOCK_SIZE=${BLOCK_SIZE}"
    echo "---------------------------------------------"
  done
done

