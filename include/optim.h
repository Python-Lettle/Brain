/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/15.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#ifndef FRAME_OPTIM_H
#define FRAME_OPTIM_H

#include <Matrix.h>
#include <Linear.h>
#include <Model.h>

double optim_BGD(Model* model, Matrix* y_pred, Matrix* target, double learning_rate);
double optim_SGD(Model* model, Matrix* y_pred, Matrix* target, double learning_rate);


#endif