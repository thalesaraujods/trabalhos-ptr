#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // Matrix* myMatrix = create_matrix(2, 2);

    // myMatrix->data[0][0] = 50;
    // myMatrix->data[0][1] = 2;
    // myMatrix->data[1][0] = 3;
    // myMatrix->data[1][1] = 4;

    // print_matrix(myMatrix);

    // destroy_matrix(&myMatrix);

    // print_matrix(myMatrix);

    Matrix* A = create_matrix(2, 2);
    Matrix* B = create_matrix(2, 3);

    // Preenche A
    A->data[0][0] = 1;  A->data[0][1] = 2;
    A->data[1][0] = 3;  A->data[1][1] = 4;

    // Preenche B
    B->data[0][0] = 10; B->data[0][1] = 20;
    B->data[1][0] = 30; B->data[1][1] = 40;

    printf("A:\n");
    print_matrix(A);
    printf("\nB:\n");
    print_matrix(B);

    Matrix* C = add_matrix(A, B);
    if (C) {
        printf("\nA + B:\n");
        print_matrix(C);
        destroy_matrix(&C);
    } else {
        fprintf(stderr, "Falha ao somar matrizes.\n");
    }

    destroy_matrix(&A);
    destroy_matrix(&B);

}