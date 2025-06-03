#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"
// Read training data 
bool Csv_Read(FILE **data_csv_read, Dataset *dataset, int result_collumn)
{
    // variable initialization
    char buffer_line[300], *token;
    int i, token_count;
    double **temp_x, **temp_y;
    unsigned int first_data_count;

    // Assign 
    dataset->layer_dim = 0;
    dataset->data_count = 0;
    first_data_count = 600;
    token_count = 0;

    *data_csv_read = fopen("../../docs/data.csv", "r");
    if (*data_csv_read == NULL)
    {
        return false;
    }

    // Count features and output's collumn
    if (fgets(buffer_line, 300, *data_csv_read) != NULL)
    {
        buffer_line[strcspn(buffer_line, '\r\n')] = '\0';
        token = strtok(buffer_line, ",");
        while (token != NULL)
        {
            token_count ++;
            token = strtok(NULL, ",");
        }
    }

    dataset->layer_dim = token_count - result_collumn;


    // allocation
    temp_x = malloc(first_data_count * sizeof(double *));
    if (!temp_x) 
    {
        fclose(*data_csv_read);
        return false;
    }
    for (i = 0; i < first_data_count; i++)
    {
        temp_x[i] = malloc(dataset->layer_dim * sizeof(double));
        if (!temp_x[i]) 
        {
            fclose(*data_csv_read);
            return false;
        }
    }

    temp_y = malloc(first_data_count * sizeof(double *));
    if (!temp_y) 
    {
        fclose(*data_csv_read);
        return false;
    }
    for (i = 0; i < first_data_count; i++)
    {
        temp_y[i] = malloc(sizeof(double));
        if (!temp_y[i]) 
        {
            fclose(*data_csv_read);
            return false;
        }
    }

    // Read data
    while (fgets(buffer_line, 300, *data_csv_read) != NULL)
    {
        buffer_line[strcspn(buffer_line, '\r\n')] = '\0';
        token = strtok(buffer_line, ",");

        temp_y[dataset->data_count][0] = atof(token);
    
        for(i = 0; i < dataset->layer_dim; i++)
        {
            temp_x[dataset->data_count][i] = atof(token);
            token = strtok(NULL, ",");
        }

       dataset->data_count ++;

        // Extend 
        if (dataset->data_count >= first_data_count)
        {
            first_data_count += 300;
            dataset->X = realloc(temp_x, first_data_count * sizeof(double *));
            dataset->Y = realloc(temp_y, first_data_count * sizeof(double *));

            if (!(dataset->X) || !(dataset->Y))
            {
                fclose(*data_csv_read);
                return false;
            }

            temp_y = dataset->Y;
            temp_x = dataset->X;

            for (i = dataset->data_count - 1; i < first_data_count; i++)
            {
                temp_x[i] = malloc(dataset->layer_dim * sizeof(double));
                if (!temp_x[i]) 
                {
                    fclose(*data_csv_read);
                    return false;
                }

                temp_y[i] = malloc(sizeof(double));
                if (!temp_y[i]) 
                {
                    fclose(*data_csv_read);
                    return false;
                }
            }
            
            
        }
    }

    // Assign  
    dataset->X = realloc(temp_x, dataset->data_count * sizeof(double *));
    dataset->Y = realloc(temp_y, dataset->data_count * sizeof(double *));

    fclose(*data_csv_read);

    return true;    
}
// Write output and model's parameter
bool Csv_Write(FILE **data_csv_write_io ,Dataset *dataset)
{
    int i, j, k, m;

    *data_csv_write_io = fopen("../../data/iodata.csv", "w");

    for(i = 0; i < dataset->data_count; i++)
    {
        fprintf(*data_csv_write_io,"%0.6f,",dataset->Y[i][0]);

        for(j = 0; j < dataset->layer_dim; j++)
        {
            fprintf(*data_csv_write_io,"%0.6f",dataset->X[i][j]);
            if (j != dataset->layer_dim - 1) fprintf(*data_csv_write_io, ",");
        }
        fprintf(*data_csv_write_io,"\n");
    }

    for(i = 0; i < dataset->layer_next_dim; i++)
    {
        for(k = 0; k < dataset->layer_dim; k++)
        {
            fprintf(*data_csv_write_io,"%0.6f",dataset->W[i][k]);
            if (k != dataset->layer_dim - 1) fprintf(*data_csv_write_io, ",");
        }
        fprintf(*data_csv_write_io,"\n");        
    }


    fclose(*data_csv_write_io);
    return true;
}
// Read output and model's parameter for backpropagation
bool Csv_Read_Bpg(FILE **data_csv_read_back, Dataset *dataset){}
// Set a new layer
bool Data_Layer_Set(Dataset *layer){}
// Free data
bool Data_Free(Dataset *dataset)
{
    int i, j;

    for(i = 0; i < dataset->data_count; i++)
    {
        free(dataset->X[i]);
        dataset->X[i] = NULL;

        free(dataset->Y[i]);
        dataset->Y[i] = NULL;

        free(dataset->X_nor[i]);
        dataset->X_nor[i] = NULL;

        free(dataset->Y_pre[i]);
        dataset->Y_pre[i] = NULL;
    }

    for(j = 0; j < dataset->layer_next_dim; j++)
    {
        free(dataset->W[j]);
        dataset->W[j] = NULL;
    }

    free(dataset->X);
    dataset->X = NULL;
    free(dataset->X_nor);
    dataset->X_nor = NULL;
    free(dataset->Y);
    dataset->Y = NULL;
    free(dataset->Y_pre);
    dataset->Y_pre = NULL;
    free(dataset->W);
    dataset->W = NULL;
    free(dataset->layer_next);
    dataset->layer_next = NULL;
    free(dataset->layer_back);
    dataset->layer_back = NULL;
    free(dataset->B);
    dataset->B = NULL;
    free(dataset);
    dataset = NULL;
}
// Free Calculation
bool Calculation_Free(double ***matrix, int row, int collumn)
{
    int i;

    for(i = 0; i < row; i++)
    {
        free(*matrix[i]);
        *matrix[i] = NULL;
    }
    *matrix = NULL;
}
// Split data for Cross Validation
bool Data_Split(Dataset *original, Dataset *train, Dataset *test, float ratio){}
// Shuffle data for Cross Validation
bool Data_Shuffle(Dataset *dataset){}
// Mormalize input data
bool Data_Normalize(Dataset *dataset){}