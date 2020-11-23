#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

Matrix* init_matrix(uint32_t nrows, uint32_t ncols) 
{
    Matrix *m = NULL;
    m = malloc(sizeof(Matrix));

    if (!m) {
        printf("Erreur de malloc pour la creation de la matrice d'utils.c");
    }

    m->data = NULL;
    m->data = (double *)malloc(nrows * ncols * sizeof(double));

    if (!m->data) { 
        printf("Erreur d'affectation de données pour la creation de la matrice d'utils.c");
    }

    m->nrows = nrows;
    m->ncols = ncols;

    return m;
}

void print_all_matrix(Matrix *m){
    double count = 0; 
    for (int i = 0; i <  m->nrows; i++) {
      for (int j = 0; j < m->ncols; j++){
         *(m->data + i*m->ncols + j) = ++count;
         printf("%f\n", *(m->data + i*m->ncols + j));
      }
    }
}

double get_matrix_value(Matrix* matrix, uint32_t row, uint32_t col) 
{
    return *(matrix->data + row * matrix->ncols + col);
}

void set_matrix_value(Matrix* matrix, uint32_t row, uint32_t col, double val) 
{
    *(matrix->data + row*matrix->ncols + col) = val;
}

void delete_matrix(Matrix** m) 
{
    free(*m);
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
double lp_norm(Matrix *matrix, uint32_t row, uint32_t column, uint32_t dim) { 
    int res = 0;

    for(int i = 1; i < row; i++){
        for (int j = 0; j < column; j++){
           //res += pow(abs(matrix->ptr[0][j] - matrix->ptr[i][j]), dim);
        }
    }

    return pow(res, 1/dim);
}