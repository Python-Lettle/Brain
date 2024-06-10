/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/3.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#include <frame.h>
#include <Matrix.h>
#include <util.h>

#include <stdio.h>

int main (void)
{
    Matrix* matrix = get_Matrix_n(1, 3, 2);
    Matrix* weights = get_Matrix_n(3, 2, 4);

    for (int i=0; i<weights->row; i++) {
        for (int j=0; j<weights->col; j++) {
            weights->data[i][j] = get_random_double(0,1);
        }
    }

    print_Matrix(matrix);
    printf("\n");
    print_Matrix(weights);

    printf("Equals: %d\n", Matrix_is_equal(matrix, weights));
    printf("\n");

    Matrix* mul = Matrix_mul(matrix, weights);
    if (mul == NULL) printf("Mul fail...\n");
    print_Matrix(mul);
    printf("\n");


    Matrix_free(mul);
    Matrix_free(matrix);
    Matrix_free(weights);

    return 0;
}