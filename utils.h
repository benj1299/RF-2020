#pragma once

typedef struct Matrix Matrix;
struct Matrix
{
    unsigned int width;
    unsigned int height;
    int* ptr;
};

Matrix matrix_create(unsigned int width, unsigned int height);
void matrix_destroy(Matrix* m);
int* matrix_row(Matrix* m, unsigned int row);
double lp_norm(Matrix *matrix, unsigned int row, unsigned int column, unsigned int dim);