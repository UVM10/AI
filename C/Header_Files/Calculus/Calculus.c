#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Data/Data.h"
#include "Calculus.h"

// Mutiply 2 matrices
double **Matrix_Multi(double **A, double **B, int row_a, int same_size, int collumn_b)
{
    double **matrix_multi;
    int i, j, k;

    matrix_multi = malloc(row_a * sizeof(double *));
    if (!matrix_multi)
    {
        perror("Failed allocation!");
        exit(1);
    }
    for (i = 0; i < row_a; i++)
    {
        matrix_multi[i] = malloc(collumn_b * sizeof(double));
        if (!matrix_multi[i])
        {
            perror("Failed allocation!");
            exit(1);
        }
    }

    for (i = 0; i < row_a; i++)
    {
        for (j = 0; j < same_size; j++)
        {
            for (k = 0; k < collumn_b; k++)
            {
                matrix_multi[i][k] += A[i][j] * B[j][k];
            }
        }
    }

    return matrix_multi;
}
// Inverse a mmatrix
void Matrix_Inverse() {}
// Transpose a matrix
void Matrix_Transpose() {}
// Determinant of a matrix
void Matrix_Det() {}
// Rank of a matrix
void Matrix_Rank() {}
// Moore-Penrose inverse of a matrix
void Matrix_Pinv() {}
// Hadamard of 2 matrices
void Matrix_Hada() {}
// Mutiply a matrix with a number
void Matrix_Scale() {}
// Dot product of a matrix
void Matrix_Dot() {}