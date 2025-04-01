#pragma once

#ifndef MATRIX_A_ROWS
#define MATRIX_A_ROWS 1024
#endif

#ifndef MATRIX_A_COLS
#define MATRIX_A_COLS 2048
#endif

#ifndef MATRIX_B_ROWS
#define MATRIX_B_ROWS 2048
#endif

#ifndef MATRIX_B_COLS
#define MATRIX_B_COLS 1024
#endif

// For consistency checks
static_assert(MATRIX_A_COLS == MATRIX_B_ROWS, "Matrix dimensions must be compatible for multiplication");

// Resulting matrix dimensions
#define MATRIX_C_ROWS MATRIX_A_ROWS
#define MATRIX_C_COLS MATRIX_B_COLS

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 32
#endif
