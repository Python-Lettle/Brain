/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#ifndef FRAME_MATRIX_H
#define FRAME_MATRIX_H

typedef struct
{
    double** data;      // 二维数组
    int row;
    int col;
}Matrix;

Matrix* get_Matrix(double* data, int row, int col);
Matrix* get_Matrix_Zeros(int row, int col);
Matrix* get_Matrix_eye(int n);
Matrix* get_Matrix_n(int row, int col, int n);
Matrix* get_Matrix_rand(int row, int col);

int Matrix_is_equal(Matrix* a, Matrix* b);

Matrix* Matrix_add(Matrix* a, Matrix* b);
Matrix* Matrix_sub(Matrix* a, Matrix* b);
Matrix* Matrix_mul(Matrix* a, Matrix* b);
Matrix* Matrix_mul_num(Matrix* a, double num);
Matrix* Matrix_mul_hadamard(Matrix* a, Matrix* b);

Matrix* Matrix_transpose(Matrix* a);

int print_Matrix(Matrix* matrix);

void Matrix_free(Matrix* matrix);

#endif