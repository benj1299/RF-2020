#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"


int main(int argc, char *argv[]) {
    
    int choice, nrows, ncols;
    double result;
    

    if (argc < 2) {
        // Exemple ./output ./datas/F0/
        perror("Data path manquant \n");
        return EXIT_FAILURE;
    }

    _count_dim_file(argv[1], &nrows, &ncols);

    int classified [nrows];
    int nombre_cluster = 2;

    Matrix* m = init_matrix(nrows, ncols);
    fulfill_matrix(m, argv[1]);
    
    //KNN Variables
    double* new_point = malloc(ncols * sizeof(double));

    printf("Menu\n\n Entrez votre choix : ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: 
            result = knn_supervised(m, new_point, 3, 2, "regression");
            printf("Result : \n%f\n", result);
            break;
        
        case 2: 
            printf("\tVeuillez choisir le nombre de cluster : \n");
            scanf("\t%d",&nombre_cluster);
            k_means(m, ncols, nombre_cluster, classified, nrows);
            for (int i = 0 ; i < nrows; i++) {
                printf ("l'élément %d fait partie de la classe : %d \n", i+1, classified[i]);
            }
            break;
        
        case 3:
            break;
        
        default: 
            printf("Ce choix n'existe pas. Veuillez en choisir un autre.");
            break;
    }
    
    delete_matrix(m);

    return EXIT_SUCCESS;
}