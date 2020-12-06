#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"

#define NB_ITEM 15
#define NB_CLUSTER 2

int main(int argc, char *argv[]) {
    
    int choice;
    unsigned int nb_dimension = 2; // J'ai pris 16 psk je teste sur la méthode E34 à 16 valeurs
    int classified [NB_ITEM];
    
    Matrix* m = init_matrix(NB_ITEM, nb_dimension);
    fulfill_matrix(m, "./datas/F0/");
    print_all_matrix(m);

    //KNN Variables
    double* new_point = malloc(m->ncols * sizeof(double));
    double result;

    // Test
    result = knn_supervised(m, new_point, 3, 2, "regression");
    printf("Result : \n%f\n", result);

/*
    scanf("Menu\n\n Entrez votre choix : %d\n", &choice);
    
    switch (choice) {
        case 1: 
            result = knn_supervised(m, new_point, 3, 2, "regression");
            printf("Result : \n%f\n", result);
            break;
        
        case 2: 
            k_means(m, nb_dimension, NB_CLUSTER, classified, NB_ITEM);
            break;
        
        case 3:
            break;
        
        default: 
            printf("Ce choix n'existe pas. Veuillez en choisir un autre.");
            break;
    }

    for (int i = 0 ; i < NB_ITEM; i++) {
        printf ("l'élément %d fait partie de la classe : %d \n", i, classified[i]);
    }
*/
    delete_matrix(m);

    return EXIT_SUCCESS;
}