#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// - FUNCAO AUXILIAR: verifica se duas matrizes têm o mesmo formato.
static int same_shape(const Matrix* a, const Matrix* b) {
    if (a == NULL || b == NULL) return 0;
    return (a->rows == b->rows) && (a->cols == b->cols);
}

// - OPERACOES: CRIAR, DESTRUIR, IMPRIMIR
Matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    Matrix* m = malloc(sizeof(Matrix));
    if (!m) return NULL;

    m->rows = rows;
    m->cols = cols;

    m->data = malloc(rows * sizeof(double*));
    if (!m->data) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        m->data[i] = calloc(cols, sizeof(double));  // já zera
        if (!m->data[i]) {
            // desaloca em caso de erro
            for (int j = 0; j < i; j++) free(m->data[j]);
            free(m->data);
            free(m);
            return NULL;
        }
    }

    return m;
}

void destroy_matrix(Matrix** mat) {
    if (*mat) {
        for (int i = 0; i < (*mat)->rows; i++) {
            free((*mat)->data[i]);
        }
        free((*mat)->data);
        free(*mat);
        *mat = NULL;
    }
}

void print_matrix(Matrix* m) {
    if (m == NULL) {
        printf("Matriz nula.\n");
        return;
    }

    printf("Matriz (%dx%d):\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%.2f\t", m->data[i][j]);
        }
        printf("\n");
    }
}

// - OPERACOES: SOMAR, SUBTRAIR, MULTIPLICAR
Matrix* add_matrix(const Matrix* a, const Matrix* b) {
    // validações básicas
    if (!same_shape(a, b)) {
        fprintf(stderr, "add_matrix: dimensoes incompativeis ou matriz nula.\n");
        return NULL;
    }

    // cria matriz resultado com mesmas dimensões
    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) {
        fprintf(stderr, "add_matrix: falha ao alocar matriz resultado.\n");
        return NULL;
    }

    // soma elemento a elemento
    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            c->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return c;
}

Matrix* sub_matrix(const Matrix* a, const Matrix* b) {
    if (!same_shape(a, b)) {
        fprintf(stderr, "sub_matrix: dimensoes incompativeis ou matriz nula.\n");
        return NULL;
    }

    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) {
        fprintf(stderr, "sub_matrix: falha ao alocar matriz resultado.\n");
        return NULL;
    }

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            c->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return c;
}

Matrix* mul_matrix(const Matrix* a, const Matrix* b) {
    if (a == NULL || b == NULL) {
        fprintf(stderr, "mul_matrix: matriz nula passada como argumento.\n");
        return NULL;
    }
    if (a->cols != b->rows) {
        fprintf(stderr, "mul_matrix: dimensoes incompativeis (%dx%d) x (%dx%d): cols(A)!=rows(B).\n",
                a->rows, a->cols, b->rows, b->cols);
        return NULL;
    }

    Matrix* c = create_matrix(a->rows, b->cols);
    if (!c) {
        fprintf(stderr, "mul_matrix: falha ao alocar matriz resultado.\n");
        return NULL;
    }

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < b->cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < a->cols; ++k) {
                sum += a->data[i][k] * b->data[k][j];
            }
            c->data[i][j] = sum;
        }
    }
    return c;
}