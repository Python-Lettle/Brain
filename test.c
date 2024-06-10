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
#include <Linear.h>
#include <Matrix.h>
#include <Model.h>
#include <util.h>

#include <stdio.h>

Matrix* x_func (Matrix* x)
{
    return x;
}

int main (void)
{
    // 数据初始化
    double data_double[2][1] = {{2},{8}};
    // double label_double[1][1] = {{1}};
    Matrix* data = get_Matrix((double*)data_double, 2, 1);
    // Matrix* label = get_Matrix((double**)label_double, 1, 1);

    // 激活函数初始化
    function_t activation = {sigmoid_Matrix, sigmoid_derivative_Matrix};

    function_t activation_x = {x_func, x_func};

    // 模型每层初始化
    Linear* linear = Linear_new(2, 3, activation);
    Linear* linear2 = Linear_new(3, 1, activation_x);

    double weights_double[3][2] = {{0.5, 0.2}, {0.7, 0.4}, {0.3, 0.3}};
    linear->weights = get_Matrix((double*)weights_double, 3, 2);

    double bias_double[3][1] = {{0.1}, {0.1}, {0.1}};
    linear->bias = get_Matrix((double*)bias_double, 3, 1);

    double weights_double2[1][3] = {{0.5, 0.3, 0.6}};
    linear2->weights = get_Matrix((double*)weights_double2, 1, 3);

    double bias_double2[1][1] = {{0.1}};
    linear2->bias = get_Matrix((double*)bias_double2, 1, 1);

    Linear* linears[] = {linear, linear2};
    Model * model = Model_new(linears, 2);

    // double lr = 0.1;

    model->forward(model, data);

    return 0;
}