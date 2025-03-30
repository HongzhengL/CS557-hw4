#pragma once

#include "Parameters.h"

void MatMatMultiply(const float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS], const float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS],
                    float (&C)[MATRIX_C_ROWS][MATRIX_C_COLS]);

void MatMatMultiplyReference(const float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS],
                             const float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS], float (&C)[MATRIX_C_ROWS][MATRIX_C_COLS]);
