#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"

#define NB_ITEM 15
#define NB_CLUSTER 2

int main(int argc, char *argv[]) {
    
    int choice, nrows, ncols;
    unsigned int nb_dimension = 2;
    double result;
    int classified [NB_ITEM];

    _count_dim_file("./datas/F0/", &nrows, &ncols);

    Matrix* m = init_matrix(nrows, ncols);
    fulfill_matrix(m, "./datas/F0/");

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
            k_means(m, nb_dimension, NB_CLUSTER, classified, NB_ITEM);
            for (int i = 0 ; i < NB_ITEM; i++) {
                printf ("l'élément %d fait partie de la classe : %d \n", i, classified[i]);
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