#include "Utilities.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <new>
#include <random>

void* AlignedAllocate(const std::size_t size, const std::size_t alignment) {
    std::size_t capacity = size + alignment - 1;
    void* ptr = new char[capacity];
    auto result = std::align(alignment, size, ptr, capacity);
    if (result == nullptr) throw std::bad_alloc();
    if (capacity < size) throw std::bad_alloc();
    return ptr;
}

void InitializeMatrices(float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS], float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> uniform_dist(-1., 1.);

    for (int i = 0; i < MATRIX_A_ROWS; i++)
        for (int j = 0; j < MATRIX_A_COLS; j++) {
            A[i][j] = uniform_dist(gen);
        }

    for (int i = 0; i < MATRIX_B_ROWS; i++)
        for (int j = 0; j < MATRIX_B_COLS; j++) {
            B[i][j] = uniform_dist(gen);
        }
}

float MatrixMaxDifference(const float (&A)[MATRIX_C_ROWS][MATRIX_C_COLS],
                          const float (&B)[MATRIX_C_ROWS][MATRIX_C_COLS]) {
    float result = 0.;
    for (int i = 0; i < MATRIX_C_ROWS; i++)
        for (int j = 0; j < MATRIX_C_COLS; j++) result = std::max(result, std::abs(A[i][j] - B[i][j]));
    return result;
}
