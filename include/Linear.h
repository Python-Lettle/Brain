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

typedef struct Linear
{
    int in_features;        // 输入特征数
    int out_features;       // 输出特征数
    double* weights;        // 权重
    double* bias;           // 偏置

    double* (*forward)(double* input);
} Linear;

#endif