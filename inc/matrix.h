#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix* create_matrix(int rows, int cols);
void destroy_matrix(Matrix** mat);
void print_matrix(Matrix* m);

#endif 