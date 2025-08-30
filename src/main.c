#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    Matrix* myMatrix = create_matrix(2, 2);

    myMatrix->data[0][0] = 50;
    myMatrix->data[0][1] = 2;
    myMatrix->data[1][0] = 3;
    myMatrix->data[1][1] = 4;

    print_matrix(myMatrix);

    destroy_matrix(&myMatrix);

    print_matrix(myMatrix);
}