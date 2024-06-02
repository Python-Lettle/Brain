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

double* forward (double* input)
{

}

void set_parameters(Linear *layer, double* weight, double* bias)
{
    layer->weights = weight;
    layer->bias = bias;
}


void* Linear_init(Linear *layer, int in_features, int out_features)
{
    layer->in_features = in_features;
    layer->out_features = out_features;
}