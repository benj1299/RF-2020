#include <stdlib.h>
#include <math.h>

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
static double lp_norm(int **matrix, int row, int column, int dim) { 
    int res = 0;

    for(int i = 1; i < row; i++){
        for (int j = 0; j < column; j++){
            res += pow(abs(matrix[0][j] - matrix[i][j]), dim);
        }
    }

    return pow(res, 1/dim);
}