#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

/*
    Permet d'initialiser une matrice avec un nombre de lignes (nrows) et de colonne (ncols) affecté en paramètre
*/
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

/*
    Permet d'afficher toutes les données d'une matrice
*/
void print_all_matrix(Matrix *m){
    double count = 0; 
    for (int i = 0; i <  m->nrows; i++) {
      for (int j = 0; j < m->ncols; j++){
          set_matrix_value(m,i, j, ++count);
          printf("%f\n", *(m->data + i*m->ncols + j));
      }
    }
}

/*
    Permet de récupérer la donnée présente à la position ("row", "col") de la matrice "matrix" fournit en paramètre
*/
double get_matrix_value(Matrix* matrix, uint32_t row, uint32_t col) 
{
    return *(matrix->data + row * matrix->ncols + col);
}

/*
    Permet d'ajouter la valeur "val" dans la matrice "matrix" à la position ("row", "col")
*/
void set_matrix_value(Matrix* matrix, uint32_t row, uint32_t col, double val) 
{
    *(matrix->data + row*matrix->ncols + col) = val;
}

/*
    Permet de libérer la mémoire d'une matrice "m"
*/
void delete_matrix(Matrix** m) 
{
    free(*m);
}

/*
    Calcule la LpNorm ou la mesure de Minkowski pour d dimensions

    Inputs :
        - matrix correspond à un pointeur de matrice (la première ligne de la matrice représente l'axe x et les lignes suivantes les points correspondants)
        - dim correspond au nombre de dimension 
        (Dim 1 -> La distance de Manhattan)
        (Dim 2 -> La distance Euclidienne)

*/
double lp_norm(Matrix *matrix, uint32_t dim) { 
    int res = 0;

    for(int i = 1; i < matrix->nrows; i++){
        for (int j = 0; j < matrix->ncols; j++){
           res += pow(fabs(get_matrix_value(matrix, 0, j) - get_matrix_value(matrix, i, j)), dim);
        }
    }

    return pow(res, 1/dim);
}