/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#include <Linear.h>

#include <stdio.h>
#include <stdlib.h>

Matrix* Linear_forward (Linear* self, Matrix* input)
{
    self->input = input;
    // mul = weights * input
    Matrix* Z = Matrix_mul(input, Matrix_transpose(self->weights));
    // printf("1. 计算隐层的加权输入 Z:\n");
    // print_Matrix(Z);
    // 将偏置加到每一行上
    for (int i=0; i<Z->row; i++) {
        for (int j=0; j<Z->col; j++) {
            Z->data[i][j] += self->bias->data[0][j];
        }
    }
    self->output = Z;
    

    Matrix* H = self->activation.calc(self->output);
    
    // printf("2. 计算隐层的激活值 H (包括偏置):\n");
    // print_Matrix(H);

    return H;
}

void Linear_init(Linear *layer, int in_features, int out_features, function_t activation)
{
    layer->in_features = in_features;
    layer->out_features = out_features;

    Matrix* weight = get_Matrix_rand(out_features, in_features);
    Matrix* bias = get_Matrix_Zeros(1, out_features);

    layer->weights = weight;
    layer->bias = bias;

    layer->forward = Linear_forward;
    layer->activation = activation;
}

void Linear_init_with_param(Linear *layer, Matrix* weight, Matrix* bias)
{
    layer->weights = weight;
    layer->bias = bias;
    
    layer->in_features = weight->row;
    layer->out_features = weight->col;

    layer->forward = Linear_forward;
}

Linear* Linear_new(int in_features, int out_features, function_t activation)
{
    Linear* layer = (Linear*)malloc(sizeof(Linear));
    Linear_init(layer, in_features, out_features, activation);
    return layer;
}