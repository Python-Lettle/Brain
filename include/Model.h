/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#ifndef FRAME_MODEL_H
#define FRAME_MODEL_H

#include <Matrix.h>
#include <Linear.h>

typedef struct Model Model;
struct Model
{
    Linear **layers;        // 模型各种网络层次
    int layer_count;        // 网络层次数量

    void* (*loss) (Matrix *pred, Matrix *label);

    Matrix* (*forward)(Model *model, Matrix *input);
    double (*backward)(Model* model, Matrix* y_pred, Matrix* target, double learning_rate);
};

Model* Model_new(Linear **layers, int layer_count);

#endif