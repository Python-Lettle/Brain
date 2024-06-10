/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#include <Model.h>

#include <stdlib.h>
#include <stdio.h>

Matrix* Model_forward(Model* model, Matrix* input)
{
    Matrix* output = input;
    for (int i = 0; i < model->layer_count; i++)
    {
        printf("Layer %d\n", i);
        output = model->layers[i]->forward(model->layers[i], output);
    }
    return output;
}

Model* Model_new(Linear **layers, int layer_count)
{
    Model* model = (Model*)malloc(sizeof(Model));
    model->layers = layers;
    model->layer_count = layer_count;

    model->forward = Model_forward;

    return model;
}

