/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */

#ifndef ML_FRAME_H
#define ML_FRAME_H

#include <Matrix.h>

typedef struct function_t function_t;
struct function_t
{
    Matrix *(*calc)(Matrix *);          // 函数本身
    Matrix *(*derivative)(Matrix *);    // 该函数的导数运算
};

typedef struct Layer_t Layer_t;
struct Layer_t
{
    int input_size;                    // 输入层大小
    int output_size;                   // 输出层大小

    // 激活函数指针
    function_t activation;

    Matrix* (*forward)(Layer_t* self, Matrix* input);
};

#endif