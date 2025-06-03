#ifndef FUNCTION_H
#define FUNCTION_H

#include<stdio.h>
#include<math.h>

// Activation function
double Sigmoid(double z);
double ReLu(double z);
void Leaky_Relu(double z);
void Softmax();
void Swish();
void GELU();
// Loss function
double MSE(double y, double y_pre, int data_count);
double MAE(double y, double y_pre, int data_count);
void Huber();
void Entropy();
void Hinge();

#endif 