/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/3.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#include <frame.h>
#include <Linear.h>
#include <Matrix.h>
#include <Model.h>
#include <util.h>

#include <stdio.h>

int main (void)
{
    // 数据初始化
    double data_double[4][4] = {
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1},
        {0,0,0,0},
    };
    Matrix* b = get_Matrix(data_double, 4, 4);

    Matrix* eye = get_Matrix_eye(4);

    Matrix* b2 = Matrix_mul(b, b);
    Matrix* b3 = Matrix_mul(b2, b);

    Matrix* a = Matrix_add(eye, b);
    a = Matrix_add(a, b2);
    a = Matrix_add(a, b3);
    // 训练过程输出
    printf("Result:\n");
    print_Matrix(a);

    return 0;
}