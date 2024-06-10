/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/3.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#ifndef FRAME_UTIL_H
#define FRAME_UTIL_H

#include <Matrix.h>

double get_random_double(double min, double max);
int get_random_int(int min, int max);

double sigmoid(double x);
double sigmoid_derivative(double x);

Matrix* sigmoid_Matrix(Matrix* x);
Matrix* sigmoid_derivative_Matrix(Matrix* x);


#endif