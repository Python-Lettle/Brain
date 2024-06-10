/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/2.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#include <frame.h>
#include <Matrix.h>
#include <util.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix* get_Matrix_eye(int n)
{
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix)); 
    if (mat == NULL) {
        return NULL;
    }
  
    // 分配内存来存储指针数组
    mat->data = (double**)malloc(n * sizeof(double*));
    if (mat->data == NULL) {
        free(mat);
        return NULL;
    }
  
    // 为每一行分配内存
    for (int i = 0; i < n; i++) {
        mat->data[i] = (double*)malloc(n * sizeof(double));
        if (mat->data[i] == NULL) {
            // 如果某行内存分配失败，则释放已分配的内存并返回NULL
            for (size_t j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL;
        }
        // 初始化该行为0
        memset(mat->data[i], 0, n * sizeof(double));
    }  
  
    for (int i = 0; i < n; i++) {
        mat->data[i][i] = 1;
    }

    mat->row = n;  
    mat->col = n;  
  
    return mat;
}

Matrix* get_Matrix(double* data, int row, int col)
{
    if (!data) {
        printf("get_Matrix: data is NULL.\n");
        return NULL;
    }

    Matrix* mat = get_Matrix_n(row, col, 0);
    if (mat == NULL) {
        printf("get_Matrix: get_Matrix_n failed.\n");
        return NULL;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mat->data[i][j] = data[i * col + j];
        }
    }
  
    return mat;
}

Matrix* get_Matrix_Zeros(int row, int col)
{
    return get_Matrix_n(row, col, 0);
}

Matrix* get_Matrix_n(int row, int col, int n)
{
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }
  
    // 分配内存来存储指针数组
    mat->data = (double**)malloc(row * sizeof(double*));
    if (mat->data == NULL) {
        free(mat);
        return NULL;
    }
  
    // 为每一行分配内存
    for (size_t i = 0; i < row; i++) {
        mat->data[i] = (double*)malloc(col * sizeof(double));
        if (mat->data[i] == NULL) {
            // 如果某行内存分配失败，则释放已分配的内存并返回NULL
            for (size_t j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL;
        }
        // 初始化该行为n
        for (size_t j = 0; j < col; j++) {
            mat->data[i][j] = n;
        }  
    }  
  
    mat->row = row;
    mat->col = col;
  
    return mat;
}

Matrix* get_Matrix_rand(int row, int col)
{
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (mat == NULL) {
        return NULL;
    }
  
    // 分配内存来存储指针数组
    mat->data = (double**)malloc(row * sizeof(double*));
    if (mat->data == NULL) {
        free(mat);
        return NULL;
    }
  
    // 为每一行分配内存
    for (size_t i = 0; i < row; i++) {
        mat->data[i] = (double*)malloc(col * sizeof(double));
        if (mat->data[i] == NULL) {
            // 如果某行内存分配失败，则释放已分配的内存并返回NULL
            for (size_t j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL;
        }
        // 初始化该行为随机数
        for (size_t j = 0; j < col; j++) {
            mat->data[i][j] = get_random_double(0,1);
        }  
    }  
  
    mat->row = row;
    mat->col = col;
  
    return mat;
}

int Matrix_is_equal(Matrix* a, Matrix* b)
{
    if (a->row != b->row || a->col != b->col) return 0;

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            if (a->data[i][j] != b->data[i][j]) return 0;
        }
    }

    return 1;
}

Matrix* Matrix_add(Matrix* a, Matrix* b)
{
    if (a->row != b->row || a->col != b->col) return NULL;
    
    Matrix* mat = get_Matrix_Zeros(a->row, a->col);
    if (mat == NULL) return NULL;

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            mat->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    
    return mat;
}
Matrix* Matrix_sub(Matrix* a, Matrix* b)
{
    if (a->row != b->row || a->col != b->col) return NULL;
    
    Matrix* mat = get_Matrix_Zeros(a->row, a->col);
    if (mat == NULL) return NULL;

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            mat->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    
    return mat;
}
Matrix* Matrix_mul(Matrix* a, Matrix* b)
{
    if (a->col != b->row) {
        printf("Matrix_mul: a.col != b.row, now a is (%d,%d), b is (%d,%d)\n",a->row, a->col,b->row,b->col);
        return NULL;
    }
    
    Matrix* mat = get_Matrix_n(a->row, b->col, 0);
    if (mat == NULL) {
        printf("Matrix_mul: malloc failed\n");
        return NULL;
    }

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < b->col; j++) {
            for (int k = 0; k < a->col; k++) {
                mat->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    
    return mat;
}


Matrix* Matrix_mul_num(Matrix* a, double num)
{
    Matrix* mat = get_Matrix_Zeros(a->row, a->col);
    if (mat == NULL) return NULL;

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            mat->data[i][j] = a->data[i][j] * num;
        }
    }
    
    return mat;
}

Matrix* Matrix_mul_hadamard(Matrix* a, Matrix* b)
{
    if (a->row != b->row || a->col != b->col) {
        printf("Matrix_mul_hadamard: a.row != b.row || a.col != b.col, now a is (%d,%d), b is (%d,%d)\n",a->row, a->col,b->row,b->col);
        return NULL;
    }
    
    Matrix* mat = get_Matrix_Zeros(a->row, a->col);
    if (mat == NULL) return NULL;
    
    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            mat->data[i][j] = a->data[i][j] * b->data[i][j];
        }
    }
    
    return mat;
}

Matrix* Matrix_transpose(Matrix* a)
{
    Matrix* mat = get_Matrix_Zeros(a->col, a->row);
    if (mat == NULL) return NULL;

    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            mat->data[j][i] = a->data[i][j];
        }
    }
    
    return mat;
}


int print_Matrix(Matrix* matrix)
{
    if (!matrix) return 0;
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->col; j++)
        {
            printf("%f\t", matrix->data[i][j]);
        }
        printf("\n");
    }

    return 1;
}

void Matrix_free(Matrix* matrix)
{
    for (int i = 0; i < matrix->row; i++) {
        free(matrix->data[i]);
    }
    
    free(matrix->data);
    free(matrix);
}