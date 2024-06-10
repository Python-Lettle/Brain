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
#include <time.h>

Matrix* x_func (Matrix* x)
{
    return x;
}
Matrix* x_de_func (Matrix* x)
{
    return 1;
}

// 自定义模型正向传播方式
Matrix* Model_forward(Model* model, Matrix* input)
{
    Matrix* output = input;
    for (int i = 0; i < model->layer_count; i++)
    {
        // printf("Layer %d\n", i);
        output = model->layers[i]->forward(model->layers[i], output);
    }
    return output;
}

int main (void)
{
    /* 初始化随机数发生器 */
    time_t t;
    srand((unsigned) time(&t));

    // 数据初始化
    double data_double[2][1] = {{2},{8}};
    double label_double[1][1] = {{1}};
    Matrix* data = get_Matrix((double*)data_double, 2, 1);
    Matrix* label = get_Matrix((double**)label_double, 1, 1);

    // 激活函数初始化
    function_t activation = {sigmoid_Matrix, sigmoid_derivative_Matrix};

    function_t activation_x = {x_func, x_de_func};

    // 模型每层初始化
    Linear* linear = Linear_new(2, 3, activation);
    Linear* linear2 = Linear_new(3, 1, activation_x);

    // double weights_double[3][2] = {{0.5, 0.2}, {0.7, 0.4}, {0.3, 0.3}};
    // linear->weights = get_Matrix((double*)weights_double, 3, 2);

    // double bias_double[3][1] = {{0.1}, {0.1}, {0.1}};
    // linear->bias = get_Matrix((double*)bias_double, 3, 1);

    // double weights_double2[1][3] = {{0.5, 0.3, 0.6}};
    // linear2->weights = get_Matrix((double*)weights_double2, 1, 3);

    // double bias_double2[1][1] = {{0.1}};
    // linear2->bias = get_Matrix((double*)bias_double2, 1, 1);

    Linear* linears[] = {linear, linear2};
    Model * model = Model_new(linears, 2);
    model->forward = Model_forward;

    double lr = 0.1;

    // 测试输出
    Matrix* y_pred = model->forward(model, data);
    printf("Before train model output = \n");
    print_Matrix(y_pred);

    printf("------------------------------\n");
    for (int i=0; i<10; i++)
    {
        printf("Train epoch %d\n", i+1);
        Model* y_pred = model->forward(model, data);
        printf("Model loss = %f\n", model->backward(model, y_pred, label, lr));
    }
    printf("------------------------------\n");

    // 测试输出
    y_pred = model->forward(model, data);
    printf("Trained model output = \n");
    print_Matrix(y_pred);

    return 0;
}