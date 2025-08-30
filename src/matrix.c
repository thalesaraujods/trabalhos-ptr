#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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