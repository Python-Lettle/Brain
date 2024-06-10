/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#ifndef FRAME_LINEAR_H
#define FRAME_LINEAR_H

#include <frame.h>
#include <Matrix.h>

typedef struct Linear Linear;
struct Linear
{
    int in_features;        // 输入特征数
    int out_features;       // 输出特征数
    Matrix* weights;        // 权重
    Matrix* bias;           // 偏置

    // 激活函数指针
    function_t activation;

    Matrix* (*forward)(Linear* self, Matrix* input);
    void (*backward)(Linear* self, double learning_rate, Matrix* y_pred, Matrix* y_true, Matrix* last_weight, Matrix* next_value);
};

void Linear_init(Linear *layer, int in_features, int out_features, function_t activation);
Linear* Linear_new(int in_features, int out_features, function_t activation);

#endif