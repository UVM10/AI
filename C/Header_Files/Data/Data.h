#ifndef DATA_H
#define DATA_H

#include<stdio.h>
#include<stdbool.h>

typedef struct
{
    double **X, **X_nor, **W, **Y, **Y_pre, *B;
    unsigned int layer_dim, data_count, layer_next_dim;
    struct Dataset *layer_next, *layer_back;
}Dataset;
// Read training data
bool Csv_Read(FILE **data_csv_read, Dataset *dataset);
// Write output and model's parameter
bool Csv_Write(FILE **data_csv_write, Dataset *dataset);
// Read output and model's parameter for backpropagation
bool Csv_Read_Bpg(FILE **data_csv_read_back, Dataset *dataset);
// Set a new layer
bool Data_Layer_Set(Dataset *layer);
// Free data 
bool Data_Free(Dataset *dataset);
// Free Calculation
bool Calculation_Free(double ***matrix);
// Split data for Cross Validation
bool Data_Split(Dataset *original, Dataset *train, Dataset *test, float ratio);
// Shuffle data for Cross Validation
bool Data_Shuffle(Dataset *dataset);
// Mormalize input data
bool Data_Normalize(Dataset *dataset);

#endif 