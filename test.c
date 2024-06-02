/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#include <frame.h>
#include <Matrix.h>

#include <stdio.h>

int main (void)
{
    Matrix* matrix = get_Matrix_n(3, 3, 6);
    Matrix* eye = get_Matrix_eye(3);

    print_Matrix(matrix);
    printf("\n");
    print_Matrix(eye);

    printf("Equals: %d\n", Matrix_is_equal(matrix, eye));
    printf("\n");

    return 0;
}