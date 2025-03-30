#include "MatMatMultiply.h"

#include "mkl.h"

alignas(64) float localA[BLOCK_SIZE][BLOCK_SIZE];
alignas(64) float localB[BLOCK_SIZE][BLOCK_SIZE];
alignas(64) float localC[BLOCK_SIZE][BLOCK_SIZE];

#pragma omp threadprivate(localA, localB, localC)

void MatMatMultiply(const float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS], const float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS],
                    float (&C)[MATRIX_C_ROWS][MATRIX_C_COLS]) {
    static constexpr int NBLOCKS_A_ROWS = MATRIX_A_ROWS / BLOCK_SIZE;
    static constexpr int NBLOCKS_A_COLS = MATRIX_A_COLS / BLOCK_SIZE;
    static constexpr int NBLOCKS_B_COLS = MATRIX_B_COLS / BLOCK_SIZE;

    // Ensure dimensions are compatible with block size
    static_assert(MATRIX_A_ROWS % BLOCK_SIZE == 0, "MATRIX_A_ROWS must be divisible by BLOCK_SIZE");
    static_assert(MATRIX_A_COLS % BLOCK_SIZE == 0, "MATRIX_A_COLS must be divisible by BLOCK_SIZE");
    static_assert(MATRIX_B_ROWS % BLOCK_SIZE == 0, "MATRIX_B_ROWS must be divisible by BLOCK_SIZE");
    static_assert(MATRIX_B_COLS % BLOCK_SIZE == 0, "MATRIX_B_COLS must be divisible by BLOCK_SIZE");

    // Ensure matrix dimensions are compatible for multiplication
    static_assert(MATRIX_A_COLS == MATRIX_B_ROWS, "Inner dimensions must match for multiplication");
    static_assert(MATRIX_C_ROWS == MATRIX_A_ROWS, "Output rows must match A rows");
    static_assert(MATRIX_C_COLS == MATRIX_B_COLS, "Output columns must match B columns");

#pragma omp parallel for
    for (int bi = 0; bi < NBLOCKS_A_ROWS; bi++) {
        for (int bj = 0; bj < NBLOCKS_B_COLS; bj++) {
            // Initialize local C block to zeros
            for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                    localC[ii][jj] = 0.0f;
                }
            }

            // Multiply blocks
            for (int bk = 0; bk < NBLOCKS_A_COLS; bk++) {
                // Load blocks from A and B into local memory
                for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                    for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                        localA[ii][jj] = A[bi * BLOCK_SIZE + ii][bk * BLOCK_SIZE + jj];
                        localB[ii][jj] = B[bk * BLOCK_SIZE + ii][bj * BLOCK_SIZE + jj];
                    }
                }

                // Perform block multiplication
                for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                    for (int kk = 0; kk < BLOCK_SIZE; kk++) {
#pragma omp simd
                        for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                            localC[ii][jj] += localA[ii][kk] * localB[kk][jj];
                        }
                    }
                }
            }

            // Store result back to C
            for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                    C[bi * BLOCK_SIZE + ii][bj * BLOCK_SIZE + jj] = localC[ii][jj];
                }
            }
        }
    }
}

void MatMatMultiplyReference(const float (&A)[MATRIX_A_ROWS][MATRIX_A_COLS],
                             const float (&B)[MATRIX_B_ROWS][MATRIX_B_COLS], float (&C)[MATRIX_C_ROWS][MATRIX_C_COLS]) {
    // Use MKL's BLAS for the reference implementation
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, MATRIX_A_ROWS, MATRIX_B_COLS, MATRIX_A_COLS, 1.0f, &A[0][0],
                MATRIX_A_COLS, &B[0][0], MATRIX_B_COLS, 0.0f, &C[0][0], MATRIX_C_COLS);
}
