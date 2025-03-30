#!/bin/bash

# --- Configuration Section ---
# Rectangular matrix multiplication parameters
RECT_A_ROWS=1024
RECT_A_COLS=4096
RECT_B_ROWS=4096
RECT_B_COLS=1024
BLOCK_SIZES=(16 32 64)

# Test different block sizes for rectangular matrices
for BLOCK_SIZE in "${BLOCK_SIZES[@]}"; do
    echo "Building rectangular matrix version with A(${RECT_A_ROWS}x${RECT_A_COLS}), B(${RECT_B_ROWS}x${RECT_B_COLS}), BLOCK_SIZE=${BLOCK_SIZE}"
    make MATRIX_A_ROWS=${RECT_A_ROWS} MATRIX_A_COLS=${RECT_A_COLS} MATRIX_B_ROWS=${RECT_B_ROWS} MATRIX_B_COLS=${RECT_B_COLS} BLOCK_SIZE=${BLOCK_SIZE}
    echo "Build complete for BLOCK_SIZE=${BLOCK_SIZE}"
    echo "---------------------------------------------"
done
