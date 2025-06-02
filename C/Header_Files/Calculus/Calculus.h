#ifndef CALCULUS_H
#define CALCULUS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Data/Data.h"

// Mutiply 2 matrices
double **Matrix_Multi(double ***A, double ***B, int row_a, int same_size, int collumn_b);
// Inverse a mmatrix
double **Matrix_Inverse(double ***A, int row_size, int column_size);
// Transpose a matrix
double **Matrix_Transpose(double ***A, int row_size, int collumn_size);
// Determinant of a matrix
void Matrix_Det();
// Rank of a matrix
void Matrix_Rank();
// Moore-Penrose inverse of a matrix
void Matrix_Pinv();
// Hadamard of 2 matrices
double **Matrix_Hada();
// Mutiply a matrix with a number
void Matrix_Scale(double ***A, int row, int collumn, double num);
// Dot product of a matrix
double Matrix_Dot(double ***A, double ***B, int row, int collumn);

#endif