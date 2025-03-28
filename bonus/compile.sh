#!/bin/bash

# Build rectangular matrix multiplication
echo "Building rectangular matrix version with A(1024x2048), B(2048x1024)"
make MATRIX_A_ROWS=1024 MATRIX_A_COLS=2048 MATRIX_B_ROWS=2048 MATRIX_B_COLS=1024 BLOCK_SIZE=32
echo "Build complete for rectangular matrix version"
echo "---------------------------------------------"

# Build square matrix versions for comparison
echo "Building square matrix version with MATRIX_SIZE=1024, BLOCK_SIZE=32"
make MATRIX_A_ROWS=1024 MATRIX_A_COLS=1024 MATRIX_B_ROWS=1024 MATRIX_B_COLS=1024 BLOCK_SIZE=32
echo "Build complete for 1024x1024 square matrix version"
echo "---------------------------------------------"

echo "Building square matrix version with MATRIX_SIZE=2048, BLOCK_SIZE=32"
make MATRIX_A_ROWS=2048 MATRIX_A_COLS=2048 MATRIX_B_ROWS=2048 MATRIX_B_COLS=2048 BLOCK_SIZE=32
echo "Build complete for 2048x2048 square matrix version"
echo "---------------------------------------------"

# Test different block sizes for rectangular matrices
for BLOCK_SIZE in 16 64; do
    echo "Building rectangular matrix version with A(1024x2048), B(2048x1024), BLOCK_SIZE=${BLOCK_SIZE}"
    make MATRIX_A_ROWS=1024 MATRIX_A_COLS=2048 MATRIX_B_ROWS=2048 MATRIX_B_COLS=1024 BLOCK_SIZE=${BLOCK_SIZE}
    echo "Build complete for BLOCK_SIZE=${BLOCK_SIZE}"
    echo "---------------------------------------------"
done
