/**
 * Copyright (C) 2024 Lettle All rights reserved.
 * See the copyright notice in the file LICENSE.
 * Created by Lettle on 2024/6/13.
 * QQ: 1071445082
 * Email: 1071445082@qq.com
 * gitee: https://gitee.com/lettle/
 * github: https://github.com/python-lettle/
 */
#include <DataLoader.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ROWS 10000
#define MAX_COLS 10000
Matrix* load_csv (const char* filename, int row, int col)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("DataLoader: Unable to open file %s", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    Matrix* mat = get_Matrix_Zeros(row, col);
    int rows = 0;
    while (fgets(line, sizeof(line), file) && rows < MAX_ROWS) {
        // 去掉换行符
        line[strcspn(line, "\n")] = '\0';

        // 分割 line 为 tokens
        char *token = strtok(line, ",");
        int col = 0;
        
        while (token && col < MAX_COLS) {
            mat->data[rows][col] = atof(token); // Convert token to double and store in array
            token = strtok(NULL, ",");
            col++;
        }
        
        rows++;
    }

    fclose(file);

    return mat;
}