#pragma once

#include <cstdlib>

#include "Parameters.h"

void* AlignedAllocate(const std::size_t size, const std::size_t alignment);
void InitializeMatrices(float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS], float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS]);
float MatrixMaxDifference(const float (&A)[MATRIX_C_ROWS][MATRIX_C_COLS],
                          const float (&B)[MATRIX_C_ROWS][MATRIX_C_COLS]);
