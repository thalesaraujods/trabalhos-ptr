#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    Matrix* A = create_matrix(2, 3);
    Matrix* B = create_matrix(2, 3);
    Matrix* D = create_matrix(3, 2);
    Matrix* Q = create_matrix(3, 3);
    Matrix* R = create_matrix(4, 4);


    // A
    A->data[0][0]=1; A->data[0][1]=2; A->data[0][2]=3;
    A->data[1][0]=4; A->data[1][1]=5; A->data[1][2]=6;

    // B
    B->data[0][0]=10; B->data[0][1]=20; B->data[0][2]=30;
    B->data[1][0]=40; B->data[1][1]=50; B->data[1][2]=60;

    // D (para A x D)
    D->data[0][0]=1; D->data[0][1]=0;
    D->data[1][0]=0; D->data[1][1]=1;
    D->data[2][0]=1; D->data[2][1]=1;

    // Q (DETERMINANTE 3X3)
    Q->data[0][0]=6; Q->data[0][1]=1;  Q->data[0][2]=1;
    Q->data[1][0]=4; Q->data[1][1]=-2; Q->data[1][2]=5;
    Q->data[2][0]=2; Q->data[2][1]=8;  Q->data[2][2]=7;

    // R (DETERMINANTE 4X4)
    double rv[] = {
        1, 2, 3, 4,
        0, 1, 4, 7,
        0, 0, 1, 3,
        0, 0, 0, 2
    };
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            R->data[i][j] = rv[i*4+j];


    Matrix* Cadd = add_matrix(A, B);
    Matrix* Csub = sub_matrix(A, B);
    Matrix* Cmul = mul_matrix(A, D);

    // --- operações com escalar ---
    double s1 = 5.0, s2 = 2.0, s3 = 3.0;
    Matrix* Cadd_scalar = add_scalar_matrix(A, s1); // A + 5
    Matrix* Csub_scalar = sub_scalar_matrix(A, s2); // A - 2
    Matrix* Cmul_scalar = mul_scalar_matrix(A, s3); // A * 3

    // --- matriz transposta ---
    Matrix* T = transpose_matrix(A);

    printf("\n###########################################\n");
    printf("------------TESTES COM MATRIZES------------\n");
    printf("###########################################\n");


    printf("\n------- MATRIZ A -------\n");
    print_matrix(A);
    printf("\n");

    printf("------- MATRIZ B -------\n");
    print_matrix(B);
    printf("\n");

    printf("------- MATRIZ D -------\n");
    print_matrix(D);
    printf("\n");

    printf("------- TESTE 1: soma de matrizes -------\n");
    printf("A + B:\n"); print_matrix(Cadd);
    printf("\n");

    printf("------- TESTE 2: subtracao de matrizes -------\n");
    printf("A - B:\n"); print_matrix(Csub);
    printf("\n");

    printf("------- TESTE 3: multipliacao de matrizes -------\n");
    printf("A x D:\n"); print_matrix(Cmul);
    printf("\n");

    printf("------- TESTE 4: soma com escalar -------\n");
    printf("A + %.2f:\n", s1); print_matrix(Cadd_scalar); printf("\n");

    printf("------- TESTE 5: subtracao com escalar -------\n");
    printf("A - %.2f:\n", s2); print_matrix(Csub_scalar); printf("\n");

    printf("------- TESTE 6: multiplicacao por escalar -------\n");
    printf("A * %.2f:\n", s3); print_matrix(Cmul_scalar); printf("\n");

    printf("------- TESTE 7: transposta da matriz A -------\n");
    print_matrix(T);
    printf("\n");

    printf("------- TESTE 8: determinante 3x3 -------\n");
    print_matrix(Q);
    printf("det(Q) = %.2f\n\n", determinant_matrix(Q));

    printf("------- TESTE 9: determinante 4x4 -------\n");
    print_matrix(R);
    printf("det(R) = %.2f\n\n", determinant_matrix(R));

    destroy_matrix(&A); destroy_matrix(&B); destroy_matrix(&D);
    destroy_matrix(&Cadd); destroy_matrix(&Csub); destroy_matrix(&Cmul);
    destroy_matrix(&Cadd_scalar); destroy_matrix(&Csub_scalar); destroy_matrix(&Cmul_scalar);
    destroy_matrix(&T);
    destroy_matrix(&Q); destroy_matrix(&R);
    
    return 0;     
}