#include <iomanip>
#include <iostream>

#include "MatMatMultiply.h"
#include "Timer.h"
#include "Utilities.h"

int main(int argc, char *argv[]) {
    // Allocate memory for matrices
    float *Araw = static_cast<float *>(AlignedAllocate(MATRIX_A_ROWS * MATRIX_A_COLS * sizeof(float), 64));
    float *Braw = static_cast<float *>(AlignedAllocate(MATRIX_B_ROWS * MATRIX_B_COLS * sizeof(float), 64));
    float *Craw = static_cast<float *>(AlignedAllocate(MATRIX_C_ROWS * MATRIX_C_COLS * sizeof(float), 64));
    float *referenceCraw = static_cast<float *>(AlignedAllocate(MATRIX_C_ROWS * MATRIX_C_COLS * sizeof(float), 64));

    // Cast raw memory to matrix types
    using matrixA_t = float(&)[MATRIX_A_ROWS][MATRIX_A_COLS];
    using matrixB_t = float(&)[MATRIX_B_ROWS][MATRIX_B_COLS];
    using matrixC_t = float(&)[MATRIX_C_ROWS][MATRIX_C_COLS];

    matrixA_t A = reinterpret_cast<matrixA_t>(*Araw);
    matrixB_t B = reinterpret_cast<matrixB_t>(*Braw);
    matrixC_t C = reinterpret_cast<matrixC_t>(*Craw);
    matrixC_t referenceC = reinterpret_cast<matrixC_t>(*referenceCraw);

    // Print dimensions and computational complexity
    std::cout << "Matrix dimensions: A(" << MATRIX_A_ROWS << "x" << MATRIX_A_COLS << ") * B(" << MATRIX_B_ROWS << "x"
              << MATRIX_B_COLS << ") = C(" << MATRIX_C_ROWS << "x" << MATRIX_C_COLS << ")" << std::endl;

    // Initialize matrices
    InitializeMatrices(A, B);
    Timer timer;

    // Correctness test
    std::cout << "Running candidate kernel for correctness test ... " << std::flush;
    timer.Start();
    MatMatMultiply(A, B, C);
    timer.Stop("Elapsed time : ");

    std::cout << "Running reference kernel for correctness test ... " << std::flush;
    timer.Start();
    MatMatMultiplyReference(A, B, referenceC);
    timer.Stop("Elapsed time : ");

    float discrepancy = MatrixMaxDifference(C, referenceC);
    std::cout << "Discrepancy between two methods : " << discrepancy << std::endl;

    // Performance test
    double elapsed_time = 0.0;
    for (int test = 1; test <= 20; test++) {
        std::cout << "Running kernel for performance run #" << std::setw(2) << test << " ... ";
        timer.Start();
        MatMatMultiply(A, B, C);
        timer.Stop("Elapsed time : ");
        elapsed_time += timer.mElapsedTime.count();
        if (test == 20) {
            std::cout << "Average elapsed time : " << elapsed_time / 20.0 << "ms" << std::endl;
        }
    }

    AlignedFree(Araw);
    AlignedFree(Braw);
    AlignedFree(Craw);
    AlignedFree(referenceCraw);

    return 0;
}
