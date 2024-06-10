/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/3.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#include <util.h>
#include <stdlib.h>
#include <math.h>

double get_random_double(double min, double max)
{
    return (double)rand() / RAND_MAX * (max - min) + min;
}
int get_random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x)
{
    return x * (1 - x);
}

Matrix* sigmoid_Matrix(Matrix* x)
{
    Matrix* result = get_Matrix_Zeros(x->row, x->col);
    for (int i = 0; i < x->row; i++)
    {
        for (int j = 0; j < x->col; j++)
        {
            result->data[i][j] = sigmoid(x->data[i][j]);
        }
    }
    return result;
}

Matrix* sigmoid_derivative_Matrix(Matrix* x)
{
    Matrix* result = get_Matrix_Zeros(x->row, x->col);
    for (int i = 0; i < x->row; i++)
    {
        for (int j = 0; j < x->col; j++)
        {
            result->data[i][j] = sigmoid_derivative(x->data[i][j]);
        }
    }
    return result;
}
