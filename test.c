/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/3.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#include <brain.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BATCH_SIZE 20
#define DATA_DIM 1
#define LABEL_DIM 1


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
    Matrix* data = load_csv("data/test/data.csv", BATCH_SIZE, DATA_DIM);
    Matrix* label = load_csv("data/test/target.csv", BATCH_SIZE, LABEL_DIM);

    // 输出数据
    // printf("Data = \n");
    // print_Matrix(data);
    // printf("Label = \n");
    // print_Matrix(label);

    // 激活函数初始化
    function_t activation_sigmoid = {sigmoid_Matrix, sigmoid_derivative_Matrix};
    function_t activation_relu = {relu_Matrix, relu_derivative_Matrix};
    function_t activation_x = {x_func, x_derivative_func};

    // 模型每层初始化
    Linear* linear = Linear_new(DATA_DIM, 8, activation_sigmoid);
    Linear* linear2 = Linear_new(8, 20, activation_relu);
    Linear* linear3 = Linear_new(20, LABEL_DIM, activation_x);

    Linear* linears[] = {linear, linear2, linear3};
    Model * model = Model_new(linears, 3);
    model->forward = Model_forward;
    model->backward = optim_SGD;

    double lr = 0.0001;

    // 测试输出
    Matrix* y_pred = model->forward(model, data);

    // printf("Loss = %f\n", model->backward(model, y_pred, label, lr));
    // model->backward(model, y_pred, label, lr);
    // printf("Before train model output = \n");
    // print_Matrix(y_pred);

    printf("------------------------------\n");
    int epochs = 1;
    double minloss = 999999;
    for (int i=0; i<epochs; i++)
    {
        Matrix* y_pred = model->forward(model, data);
        double loss = model->backward(model, y_pred, label, lr);
        if (loss < minloss) minloss = loss;
        if (i%200==199 || i==0)
            printf("Epoch(%d/%d) loss = %f\n", i+1, epochs, loss);
    }
    printf("------------------------------\n");
    
    printf("Min loss = %f\n", minloss);
    // 输出结果保存
    y_pred = model->forward(model, data);
    printf("Model output saved. \n");
    save_Matrix(y_pred, "pred.csv");

    // printf("Target = \n");
    // print_Matrix(label);

    return 0;
}