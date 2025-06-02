#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Calculus.h"

// Mutiply 2 matrices
double **Matrix_Multi(double ***A, double ***B, int row_a, int same_size, int collumn_b)
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
                matrix_multi[i][k] += *A[i][j] * *B[j][k];
            }
        }
    }

    return matrix_multi;
}
// Inverse a mmatrix using LU/Cholesky	
double **Matrix_Inverse(double ***A, int row_size, int column_size) 
{
    int n = row_size;
    if (n != column_size) return NULL; // Không phải ma trận vuông

    // Cấp phát động cho các ma trận
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    double **P = (double **)malloc(n * sizeof(double *));
    double **A_copy = (double **)malloc(n * sizeof(double *));
    double **A_inv = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        L[i] = (double *)calloc(n, sizeof(double));
        U[i] = (double *)calloc(n, sizeof(double));
        P[i] = (double *)calloc(n, sizeof(double));
        A_copy[i] = (double *)calloc(n, sizeof(double));
        A_inv[i] = (double *)calloc(n, sizeof(double));
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = *A[i][j];
            P[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // PLU decomposition with partial pivoting
    for (int k = 0; k < n; k++) {
        // Tìm pivot lớn nhất
        int pivot = k;
        double max_val = fabs(A_copy[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(A_copy[i][k]) > max_val) {
                max_val = fabs(A_copy[i][k]);
                pivot = i;
            }
        }

        // Nếu pivot quá nhỏ, coi như không khả nghịch
        if (fabs(max_val) < 1e-12) {
            for (int i = 0; i < n; i++) {
                free(L[i]); free(U[i]); free(P[i]); free(A_copy[i]); free(A_inv[i]);
            }
            free(L); free(U); free(P); free(A_copy); free(A_inv);
            return NULL;
        }

        // Hoán vị nếu cần
        if (pivot != k) {
            double *tmp = A_copy[k]; A_copy[k] = A_copy[pivot]; A_copy[pivot] = tmp;
            tmp = P[k]; P[k] = P[pivot]; P[pivot] = tmp;
            if (k > 0) {
                for (int j = 0; j < k; j++) {
                    double t = L[k][j];
                    L[k][j] = L[pivot][j];
                    L[pivot][j] = t;
                }
            }
        }

        // Gán L và U
        for (int i = k + 1; i < n; i++) {
            L[i][k] = A_copy[i][k] / A_copy[k][k];
            for (int j = k; j < n; j++)
                A_copy[i][j] -= L[i][k] * A_copy[k][j];
        }
        for (int j = k; j < n; j++)
            U[k][j] = A_copy[k][j];
    }

    for (int i = 0; i < n; i++) L[i][i] = 1.0;

    // Giải LUx = Pb cho từng cột
    for (int col = 0; col < n; col++) {
        double *e = (double *)calloc(n, sizeof(double));
        double *b = (double *)calloc(n, sizeof(double));
        double *y = (double *)calloc(n, sizeof(double));
        double *x = (double *)calloc(n, sizeof(double));
        e[col] = 1.0;

        for (int i = 0; i < n; i++) {
            b[i] = 0.0;
            for (int j = 0; j < n; j++)
                b[i] += P[i][j] * e[j];
        }

        // forward: Ly = b
        for (int i = 0; i < n; i++) {
            y[i] = b[i];
            for (int j = 0; j < i; j++)
                y[i] -= L[i][j] * y[j];
        }

        // backward: Ux = y
        for (int i = n - 1; i >= 0; i--) {
            if (fabs(U[i][i]) < 1e-12) {
                // Trường hợp bất thường, không thể chia
                free(e); free(b); free(y); free(x);
                for (int i = 0; i < n; i++) {
                    free(L[i]); free(U[i]); free(P[i]); free(A_copy[i]); free(A_inv[i]);
                }
                free(L); free(U); free(P); free(A_copy); free(A_inv);
                return NULL;
            }
            x[i] = y[i];
            for (int j = i + 1; j < n; j++)
                x[i] -= U[i][j] * x[j];
            x[i] /= U[i][i];
        }

        // Gán cột kết quả vào A^-1
        for (int i = 0; i < n; i++)
            A_inv[i][col] = x[i];

        free(e); free(b); free(y); free(x);
    }

    for (int i = 0; i < n; i++) {
        free(L[i]); free(U[i]); free(P[i]); free(A_copy[i]);
    }
    free(L); free(U); free(P); free(A_copy);

    return A_inv;
}
// Transpose a matrix
double **Matrix_Transpose(double ***A, int row_size, int collumn_size) 
{
    double **matrix_trans;
    int i, j, k;

    matrix_trans = malloc(collumn_size * sizeof(double*));
    if(!matrix_trans)
    {
        perror("Failed allocation");
    }
    for(i = 0; i < collumn_size; i++)
    {
        matrix_trans[i] = malloc(row_size * sizeof(double));
    }

    for(i = 0; i < row_size; i++)
    {
        for(k = 0; k < collumn_size; k++)
        {
            matrix_trans[k][i] = *A[i][k];
        }
    }

    return matrix_trans;
}
// Determinant of a matrix
void Matrix_Det() {}
// Rank of a matrix
void Matrix_Rank() {}
// Moore-Penrose inverse of a matrix
void Matrix_Pinv() {}
// Hadamard of 2 matrices
double **Matrix_Hada(double ***A, double ***B, int row, int collumn)
{
    double ** matrix_hadamard;
    int i, j;

    matrix_hadamard = malloc(row * sizeof(double*));
    if(!matrix_hadamard) return NULL;
    for(i = 0; i < row; i++)
    {
        matrix_hadamard[i] = malloc(collumn * sizeof(double));
        if(!matrix_hadamard[i]) return NULL;
    }

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < collumn; j++)
        {
            matrix_hadamard[i][j] = *A[i][j] * *B[i][j];
        }
    }
}
// Mutiply a matrix with a number
void Matrix_Scale(double ***A, int row, int collumn, double num)
{
    int i, j;
    
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < collumn; j++)
        {
            *A[i][j] *= num;
        }
    }
}
// Dot product of a matrix
double Matrix_Dot(double ***A, double ***B, int row, int collumn) 
{
    double result;
    int i,j;
    result = 0;

    for(i = 0; i < row; i ++)
    {
        for(j = 0; j < collumn; j++)
        {
            result += *A[i][j] * *B[i][j];
        }
    }

    return result;
}