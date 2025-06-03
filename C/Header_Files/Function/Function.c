#include<stdio.h>
#include<math.h>
#include"Function.h"

// Activation function
double Sigmoid(double z)
{
    return 1/(1 + exp(z));
}
double ReLu(double z)
{
    return (z > 0) ? z : 0;
}
void Leaky_Relu(double z)
{
    double alpha;

    alpha = 0.01;
    
    return (z > 0) ? z : alpha*z;
}
void Softmax(double **z, double **a, int collumn)
{
    double result, max_z;
    int i;

    result = 0;
    max_z = *z[0];
    
    for(i = 0; i < collumn; i++)
    {
        if(*z[i] > max_z) max_z = *z[i];
    }

    for(i = 0; i < collumn; i++)
    {
        *z[i] -= max_z;
        result += exp(*z[i]);
    }

    for(i = 0; i < collumn; i++)
    {
        *a[i] = (exp(*z[i]))/result;
    }
}
void Swish(){}
void GELU(){}
// Loss function
double MSE(double y, double y_pre, int data_count)
{
    return (1/(double)data_count) * pow((y - y_pre), 2);
}
double MAE(double y, double y_pre, int data_count)
{
    return (1/(double)data_count) * abs(y - y_pre);
}
void Huber(){}
void Entropy(){}
void Hinge(){}