import csv
import matplotlib as plt

X = []
Y = []
data_point = 0 
token = 0

def Data_Csv_Read():
    with open('D:\Python_and_ML\EDABK\docs\LiR_Housing.csv', mode = 'r', newline='', encoding='utf-8') as file:
        global X, Y, data_point, token
        reader = csv.reader(file)
        header = next(reader)
        token = len(header) - 1
        for line in reader:
            if not line:
                continue
            data_point += 1
            Y.append([int(line.pop(0))])
            X.append(list(map(lambda features: 1 if features == 'yes' or features == 'furnished' else (0 if features == 'no' or features == 'unfurnished' else (0.5 if features == 'semi-furnished' else int(features))), line)))
            X[data_point-1].insert(0, 1)
        token += 1

def Linear_Regression():
    global X, Y, data_point, token
    
    def Matrix_Duplication(matrix_first, matrix_second, row_size_first, same_size, collumn_size_second):
        matrix = [[0 for index in range(collumn_size_second)] for index in range(row_size_first)]
        for index_row_first in range(row_size_first):
            for index_same in range(same_size):
                for index_collumn_second in range(collumn_size_second):
                    matrix[index_row_first][index_collumn_second] += matrix_first[index_row_first][index_same] * matrix_second[index_same][index_collumn_second]
        return matrix

    def Matrix_Inverse(matrix):
        size = len(matrix)
        matrix_identity = [[1 if row == collumn else 0 for collumn in range(size)] for row in range(size)]
        matrix_combine = [row[:] + identity_row[:] for row, identity_row in zip(matrix, matrix_identity)]

        for row in range(size):
            if matrix_combine[row][row] == 0:
                for collumn in range(row+1, size):
                    if matrix_combine[collumn][row] != 0:
                        matrix_combine[row], matrix_combine[collumn] = matrix_combine[collumn], matrix_combine[row]
                        break

            pivot = matrix_combine[row][row]
            matrix_combine[row] = [x / pivot for x in matrix_combine[row]]

            for collumn_nd in range(size):
                if row != collumn_nd:
                    ratio = matrix_combine[collumn_nd][row]
                    matrix_combine[collumn_nd] = [aj - ratio * ai for aj, ai in zip(matrix_combine[collumn_nd], matrix_combine[row])]

        inverse_matrix = [row[size:] for row in matrix_combine]
        return inverse_matrix
    
    def Matrix_Transpose(matrix_origin, row_size, collumn_size):
        matrix_inverse = [[0 for index in range(row_size)] for index in range(collumn_size)]
        for row in range(row_size):
            for collumn in range(collumn_size):
                matrix_inverse[collumn][row] = matrix_origin[row][collumn]
        return matrix_inverse

    X_matrix = Matrix_Transpose(X, data_point, token)

    W = [[0] for index in range(token)]
    W = (Matrix_Duplication(Matrix_Duplication(Matrix_Inverse(Matrix_Duplication(X_matrix, X, token, data_point, token)), X_matrix, token, token, data_point), Y, token, data_point, 1))

    return W

Data_Csv_Read()
W = Linear_Regression()
print(W)