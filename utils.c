#include <stdlib.h>
#include <math.h>
#include "utils.h"

Matrix matrix_create(unsigned int width, unsigned int height)
{
    struct Matrix new_matrix;

    new_matrix.width = width;
    new_matrix.height = height;
    new_matrix.ptr = malloc(width * height * sizeof(int));

    return new_matrix;
}

void matrix_destroy(Matrix* m)
{
    free(m->ptr);
}

int* matrix_row(Matrix* m, unsigned int row)
{
    return m->ptr + row * m->width;
}

/*
    Calcule la LpNorm ou la mesure de Minkowski pour d dimensions

    Inputs :
        - matrix correspond à un pointeur de matrice (la première ligne de la matrice représente l'axe x et les lignes suivantes les points correspondants)
        - row correspond au nombre de lignes de la matrice
        - column au nombre de colonne de la matrice
        - dim correspond au nombre de dimension 
        (Dim 1 -> La distance de Manhattan)
        (Dim 2 -> La distance Euclidienne)

*/
double lp_norm(Matrix *matrix, unsigned int row, unsigned int column, unsigned int dim) { 
    int res = 0;

    for(int i = 1; i < row; i++){
        for (int j = 0; j < column; j++){
            //res += pow(abs(matrix->ptr[0][j] - matrix->ptr[i][j]), dim);
        }
    }

    return pow(res, 1/dim);
}