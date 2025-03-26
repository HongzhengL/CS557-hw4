#pragma once

#include <cstdlib>

#include "Parameters.h"

void* AlignedAllocate(const std::size_t size, const std::size_t alignment);
void InitializeMatrices(float (&A)[MATRIX_SIZE][MATRIX_SIZE], float (&B)[MATRIX_SIZE][MATRIX_SIZE]);
