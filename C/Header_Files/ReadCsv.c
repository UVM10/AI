#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Csv.h"

bool Read_Csv(FILE **data_csv_read, int ***X, int **Y, unsigned int *features_count, unsigned int *data_count)
{
    // variable initialization
    char buffer_line[300], *token;
    int i, **temp_x, *temp_y;
    unsigned int first_data_count;

    // Assign 
    *features_count = 0;
    *data_count = 0;
    first_data_count = 600;

    *data_csv_read = fopen("../../data/data.csv", "r");
    if (*data_csv_read == NULL)
    {
        return false;
    }

    // Count features
    if (fgets(buffer_line, 300, *data_csv_read) != NULL)
    {
        buffer_line[strcspn(buffer_line, '\r\n')] = '\0';
        token = strtok(buffer_line, ",");
        while (token != NULL)
        {
            (*features_count)++;
            token = strtok(NULL, ",");
        }
    }


    // allocation
    temp_x = malloc(first_data_count * sizeof(int *));
    if (!temp_x) 
    {
        fclose(*data_csv_read);
        return false;
    }
    for (i = 0; i < first_data_count; i++)
    {
        temp_x[i] = malloc(*features_count * sizeof(int));
        if (!temp_x[i]) 
        {
            fclose(*data_csv_read);
            return false;
        }
    }

    temp_y = malloc(first_data_count * sizeof(int));
    if (!temp_y) 
    {
        fclose(*data_csv_read);
        return false;
    }

    // Read data
    while (fgets(buffer_line, 300, *data_csv_read) != NULL)
    {
        buffer_line[strcspn(buffer_line, '\r\n')] = '\0';
        token = strtok(buffer_line, ",");
        for (i = 0; i < *features_count; i++)
        {
            if (i == 0) temp_y[*data_count] = atoi(token);
            temp_x[*data_count][i] = atoi(token);
            token = strtok(NULL, ",");
        }

        (*data_count)++;

        // Extend 
        if (*data_count >= first_data_count)
        {
            first_data_count += 300;
            *X = realloc(temp_x, first_data_count * sizeof(int *));
            *Y = realloc(temp_y, first_data_count * sizeof(int));

            if (!(*X) || !(*Y))
            {
                fclose(*data_csv_read);
                return false;
            }

            temp_y = *Y;
            temp_x = *X;

            for (i = *data_count - 1; i < first_data_count; i++)
            {
                temp_x[i] = malloc(*features_count * sizeof(int));
                if (!temp_x[i]) 
                {
                    fclose(*data_csv_read);
                    return false;
                }
            }
            
            
        }
    }

    // Assign  
    *X = realloc(temp_x, *data_count * sizeof(int *));
    *Y = realloc(temp_y, *data_count * sizeof(int));

    fclose(*data_csv_read);

    return true;    
}

bool Write_Csv(FILE **data_csv_write, int **Bias, int **W_optimized, int Bias_row, int Bias_collumn, int W_rows, int W_collumn)
{

}