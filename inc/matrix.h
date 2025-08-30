#ifndef MATRIX_H
#define MATRIX_H

// - DEFINICAO: MATRIZ
typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

// - OPERACOES: CRIAR, DESTRUIR, IMPRIMIR
Matrix* create_matrix(int rows, int cols);
void destroy_matrix(Matrix** mat);
void print_matrix(Matrix* m);

// - OPERACOES: SOMAR, SUBTRAIR, MULTIPLICAR
Matrix* add_matrix(const Matrix* a, const Matrix* b);
Matrix* sub_matrix(const Matrix* a, const Matrix* b);
Matrix* mul_matrix(const Matrix* a, const Matrix* b);

#endif 