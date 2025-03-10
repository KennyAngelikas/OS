#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>  // For gettimeofday()

#define N 500 // Change to 1000 (or another size) for performance testing

// Function Prototypes
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N], int order);
void printMatrix(int matrix[N][N]);
void saveMatrixToFile(const char *filename, int matrix[N][N]);

int main(int argc, char *argv[]) {
    // 1) Determine loop order from command-line
    // Default = 1 => (i, j, k)
    int order = 1;
    if (argc > 1) {
        order = atoi(argv[1]);
        if (order < 1 || order > 6) {
            printf("Invalid loop order. Please use 1..6\n");
            return 1;
        }
    }

    // 2) Define two example matrices A and B
    // For larger N, you might fill them with random data or read from a file
    int A[N][N];
    int B[N][N];
    int C[N][N]; // Result matrix

    // Fill A and B with some values
    // (Here, just a simple pattern; adapt as you see fit)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;      // Example pattern
            B[i][j] = (i + 1) * (j + 1);
        }
    }

    // 3) TIME ONLY the matrix multiplication (exclude input gen & file output)
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // Multiply matrices using selected loop order
    multiplyMatrices(A, B, C, order);

    gettimeofday(&endTime, NULL);

    // Calculate time difference
    double elapsedTime = (endTime.tv_sec - startTime.tv_sec)
                       + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

    // 4) Print result to console
    printf("Result of matrix multiplication (loop order %d):\n", order);
    // For large N, consider printing only partial results or skipping entirely
    printMatrix(C);

    printf("\nTime taken for multiplication (order %d): %.6f seconds\n", order, elapsedTime);

    // 5) Save to file (e.g., "result_order3.txt") - not timed
    char filename[50];
    sprintf(filename, "result_order%d.txt", order);
    saveMatrixToFile(filename, C);
    printf("Saved matrix to file: %s\n", filename);

    return 0;
}

// Core multiplication with 6 possible loop orders
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N], int order) {
    // First, set C to 0
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0;

    switch (order) {
        case 1: // (i, j, k)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;

        case 2: // (i, k, j)
            for (int i = 0; i < N; i++) {
                for (int k = 0; k < N; k++) {
                    for (int j = 0; j < N; j++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;

        case 3: // (j, i, k)
            for (int j = 0; j < N; j++) {
                for (int i = 0; i < N; i++) {
                    for (int k = 0; k < N; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;

        case 4: // (j, k, i)
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    for (int i = 0; i < N; i++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;

        case 5: // (k, i, j)
            for (int k = 0; k < N; k++) {
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;

        case 6: // (k, j, i)
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    for (int i = 0; i < N; i++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            break;
    }
}

// Print an N×N matrix to console
void printMatrix(int matrix[N][N]) {
    // For very large N, consider printing only partial slices
    // to avoid huge console dumps.
    for (int i = 0; i < (N < 6 ? N : 6); i++) {
        for (int j = 0; j < (N < 6 ? N : 6); j++) {
            printf("%d ", matrix[i][j]);
        }
        if (N > 6) printf("... ");
        printf("\n");
    }
    if (N > 6) printf("... (truncated for large N)\n");
}

// Save an N×N matrix to a file
void saveMatrixToFile(const char *filename, int matrix[N][N]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(fp, "%d ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
