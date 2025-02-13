
/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/15.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#include <optim.h>

#include <stdio.h>
double MSELoss(Matrix* y_pred, Matrix* target)
{
    double loss = 0.0;
    for (int i=0; i<y_pred->row; i++)
    {
        for (int j=0; j<y_pred->col; j++)
        {
            double delta = y_pred->data[i][j] - target->data[i][j];
            loss += delta * delta;
        }
    }
    return loss / 2;
}
double optim_BGD(Model* model, Matrix* y_pred, Matrix* target, double learning_rate)
{
    // printf("y_pred: \n");
    // print_Matrix(y_pred);
    // printf("target: \n");
    // print_Matrix(target);
    double loss = MSELoss(y_pred, target);
    // printf("Loss: %f\n", loss);

    // 先计算输出层的误差
    Matrix* delta = Matrix_sub(y_pred, target);

    // printf("Output Layer error:\n");
    // print_Matrix(delta);

    // 输出层的权重和偏置的梯度
    Matrix* E_W_grad = Matrix_mul(Matrix_transpose(delta), model->layers[model->layer_count-1]->input);
    Matrix* E_b_grad = get_Matrix_Zeros(model->layers[model->layer_count-1]->bias->row, model->layers[model->layer_count-1]->bias->col);
    for (int i=0; i<delta->row; i++)
    {
        for (int j=0; j<delta->col; j++)
        {
            E_b_grad->data[0][j] += delta->data[i][j];
        }
    }
    E_b_grad = Matrix_mul_num(E_b_grad, learning_rate);

    // printf("E_W_grad:\n");
    // print_Matrix(E_W_grad);
    // printf("E_b_grad:\n");
    // print_Matrix(E_b_grad);

    // 更新输出层权重和偏置
    // printf("Output Layer weights and bias after update:\n");

    model->layers[model->layer_count-1]->weights = Matrix_sub(model->layers[model->layer_count-1]->weights, Matrix_mul_num(E_W_grad, learning_rate));
    // print_Matrix(model->layers[model->layer_count-1]->weights);
    model->layers[model->layer_count-1]->bias = Matrix_sub(model->layers[model->layer_count-1]->bias, E_b_grad);
    // printf("--------------------\n");
    // print_Matrix(model->layers[model->layer_count-1]->bias);

    Matrix *activation_derivative;
    for (int i=model->layer_count-2; i>=0; i--)
    {
        // 传播误差到隐层 i
        // 先传播误差 delta
        delta = Matrix_mul(delta, model->layers[i+1]->weights);
        
        // 再计算激活函数的导数
        activation_derivative = model->layers[i]->activation.derivative(model->layers[i]->output);

        // 隐层误差项 逐元素乘 激活函数的导数
        delta = Matrix_mul_hadamard(delta, activation_derivative);
        // printf("Hidden Layer %d error:\n", i);
        // print_Matrix(delta);

        // 隐层权重和偏置的梯度
        E_W_grad = Matrix_mul(Matrix_transpose(delta), model->layers[i]->input);
        // E_W_grad = Matrix_add(E_W_grad, Matrix_mul_num(get_Matrix_rand(E_W_grad->row, E_W_grad->col), 2));
        E_b_grad = get_Matrix_Zeros(model->layers[i]->bias->row, model->layers[i]->bias->col);
        for (int i=0; i<delta->row; i++) {
            for (int j=0; j<delta->col; j++) {
                E_b_grad->data[0][j] += delta->data[i][j];
            }
        }
        E_b_grad = Matrix_mul_num(E_b_grad, learning_rate);
        // E_b_grad = Matrix_add(E_b_grad, Matrix_mul_num(get_Matrix_rand(E_b_grad->row, E_b_grad->col), 2));
        // printf("E_W_grad:\n");
        // print_Matrix(E_W_grad);
        // printf("E_b_grad:\n");
        // print_Matrix(E_b_grad);

        // 更新隐层权重和偏置
        model->layers[i]->weights = Matrix_sub(model->layers[i]->weights, Matrix_mul_num(E_W_grad, learning_rate));
        model->layers[i]->bias = Matrix_sub(model->layers[i]->bias, E_b_grad);

        // printf("Layer %d weights and bias after update:\n", i);
        // print_Matrix(model->layers[i]->weights);
        // printf("--------------------\n");
        // print_Matrix(model->layers[i]->bias);
    }

    return loss;
}

double optim_SGD(Model* model, Matrix* y_pred, Matrix* target, double learning_rate)
{

    Matrix* E_W_grad, *E_b_grad;

    double loss = MSELoss(y_pred, target);

    // 先计算输出层的误差
    Matrix* delta = Matrix_sub(y_pred, target);
    printf("output layer delta:\n");
    print_Matrix(delta);

    printf("Output layer weights:\n");
    print_Matrix(model->layers[model->layer_count-1]->weights);
    E_W_grad = Matrix_mul(Matrix_transpose(delta), model->layers[model->layer_count-1]->input);
    E_b_grad = get_Matrix_Zeros(model->layers[model->layer_count-1]->bias->row, model->layers[model->layer_count-1]->bias->col);
    for (int i=0; i<delta->row; i++)
    {
        for (int j=0; j<delta->col; j++)
        {
            E_b_grad->data[0][j] += delta->data[i][j];
        }
    }
    E_W_grad = Matrix_mul_num(E_W_grad, learning_rate);
    E_b_grad = Matrix_mul_num(E_b_grad, learning_rate);

    printf("E_W_grad:\n");
    print_Matrix(E_W_grad);
    printf("E_b_grad:\n");
    print_Matrix(E_b_grad);

    // 更新权重
    model->layers[model->layer_count-1]->weights = Matrix_sub(model->layers[model->layer_count-1]->weights, E_W_grad);
    model->layers[model->layer_count-1]->bias = Matrix_sub(model->layers[model->layer_count-1]->bias, E_b_grad);

    for (int i=model->layer_count-2; i>=0; i--)
    {
        // 先传播误差 delta
        delta = Matrix_mul(delta, model->layers[i+1]->weights);
        
        // 再计算激活函数的导数
        Matrix* activation_derivative = model->layers[i]->activation.derivative(model->layers[i]->output);

        // 隐层误差项 逐元素乘 激活函数的导数
        delta = Matrix_mul_hadamard(delta, activation_derivative);
        printf("hidden layer delta:\n");
        print_Matrix(delta);

        printf("hidden layer weights:\n");
        print_Matrix(model->layers[model->layer_count-1]->weights);
        E_W_grad = Matrix_mul(Matrix_transpose(delta), model->layers[model->layer_count-1]->input);
        E_b_grad = get_Matrix_Zeros(model->layers[model->layer_count-1]->bias->row, model->layers[model->layer_count-1]->bias->col);
        for (int i=0; i<delta->row; i++)
        {
            for (int j=0; j<delta->col; j++)
            {
                E_b_grad->data[0][j] += delta->data[i][j];
            }
        }
        E_W_grad = Matrix_mul_num(E_W_grad, learning_rate);
        E_b_grad = Matrix_mul_num(E_b_grad, learning_rate);

        printf("E_W_grad:\n");
        print_Matrix(E_W_grad);
        printf("E_b_grad:\n");
        print_Matrix(E_b_grad);

        // 更新权重
        model->layers[model->layer_count-1]->weights = Matrix_sub(model->layers[model->layer_count-1]->weights, E_W_grad);
        model->layers[model->layer_count-1]->bias = Matrix_sub(model->layers[model->layer_count-1]->bias, E_b_grad);
    }

    return loss;
}