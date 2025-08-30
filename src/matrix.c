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

// - OPERACOES MATRIZ: CRIAR, DESTRUIR, IMPRIMIR
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

// - OPERACOES ENTRE MATRIZES: SOMAR, SUBTRAIR, MULTIPLICAR
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

// - OPERACOES COM ESCALAR: SOMAR, SUBTRAIR, MULTIPLICAR
Matrix* add_scalar_matrix(const Matrix* a, double scalar) {
    if (!a) {
        fprintf(stderr, "add_scalar_matrix: matriz nula.\n");
        return NULL;
    }
    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) return NULL;

    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            c->data[i][j] = a->data[i][j] + scalar;

    return c;
}

Matrix* sub_scalar_matrix(const Matrix* a, double scalar) {
    if (!a) {
        fprintf(stderr, "sub_scalar_matrix: matriz nula.\n");
        return NULL;
    }
    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) return NULL;

    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            c->data[i][j] = a->data[i][j] - scalar;

    return c;
}

Matrix* mul_scalar_matrix(const Matrix* a, double scalar) {
    if (!a) {
        fprintf(stderr, "mul_scalar_matrix: matriz nula.\n");
        return NULL;
    }
    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) return NULL;

    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            c->data[i][j] = a->data[i][j] * scalar;

    return c;
}

// - OPERACAO: MATRIZ TRANSPOSTA
Matrix* transpose_matrix(const Matrix* a) {
    if (!a) {
        fprintf(stderr, "transpose_matrix: matriz nula.\n");
        return NULL;
    }

    // cria a transposta com dimensões invertidas
    Matrix* t = create_matrix(a->cols, a->rows);
    if (!t) {
        fprintf(stderr, "transpose_matrix: falha ao alocar matriz transposta.\n");
        return NULL;
    }

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            t->data[j][i] = a->data[i][j];
        }
    }

    return t;
}

// - OPERACAO: DETERMINANTE
static Matrix* clone_matrix(const Matrix* a) {
    if (!a) return NULL;
    Matrix* c = create_matrix(a->rows, a->cols);
    if (!c) return NULL;
    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            c->data[i][j] = a->data[i][j];
    return c;
}

double determinant_matrix(const Matrix* a) {
    if (!a) {
        fprintf(stderr, "determinant_matrix: matriz nula.\n");
        return 0.0;
    }
    if (a->rows != a->cols) {
        fprintf(stderr, "determinant_matrix: matriz nao quadrada (%dx%d).\n", a->rows, a->cols);
        return 0.0;
    }

    const int n = a->rows;
    const double EPS = 1e-12;

    Matrix* m = clone_matrix(a);
    if (!m) {
        fprintf(stderr, "determinant_matrix: falha ao clonar matriz.\n");
        return 0.0;
    }

    int swaps = 0;

    for (int k = 0; k < n; ++k) {
        /* pivotamento parcial: escolhe a maior |entrada| na coluna k, linhas k..n-1 */
        int p = k;
        double best = fabs(m->data[k][k]);
        for (int i = k + 1; i < n; ++i) {
            double val = fabs(m->data[i][k]);
            if (val > best) { best = val; p = i; }
        }

        /* se o melhor pivô é ~0, determinante = 0 (matriz singular) */
        if (best < EPS) {
            destroy_matrix(&m);
            return 0.0;
        }

        /* troca de linha se necessário */
        if (p != k) {
            double* tmp = m->data[p];
            m->data[p] = m->data[k];
            m->data[k] = tmp;
            swaps++;
        }

        /* elimina entradas abaixo do pivô */
        double pivot = m->data[k][k];
        for (int i = k + 1; i < n; ++i) {
            double factor = m->data[i][k] / pivot;
            /* começa em k para aproveitar o zero que vai surgindo à esquerda */
            for (int j = k; j < n; ++j) {
                m->data[i][j] -= factor * m->data[k][j];
            }
        }
    }

    /* produto da diagonal = det(U); ajusta sinal pelas trocas */
    double det = 1.0;
    for (int i = 0; i < n; ++i) det *= m->data[i][i];
    if (swaps % 2 != 0) det = -det;

    destroy_matrix(&m);
    return det;
}
