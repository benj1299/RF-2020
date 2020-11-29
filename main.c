#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"

#define NB_ITEM 11
#define NB_CLUSTER 9

// Matrice 9 * 11 


int main(int argc, char *argv[]) {

    unsigned int nb_dimension = 16; // J'ai pris 16 psk je teste sur la méthode E34 à 16 valeurs

    // On Initialise la matrice qui va représenter la base
    Matrix* base_apprentissage = init_matrix(NB_ITEM,nb_dimension);
    // On remplie les valeurs de la matrices
    fulfill_matrix(base_apprentissage,"test.achanger");

    k_means(base_apprentissage,nb_dimension,NB_CLUSTER,1);

    return EXIT_SUCCESS;
}

// Fonctionne chez benjy mais pas moi

    /*unsigned int row = 10;
    unsigned column = 10;
    double val = 0; 

    Matrix *m = init_matrix(row, column);
    fulfill_matrix(m, "./datas/E34");
    double* new_point = malloc(m->ncols * sizeof(double));

    double result = knn_supervised(m, new_point, 3, 2, "regression");

    printf("Result : \n%f\n", result);

/*
    char choice;
    do {
        printf("Menu\n\n");
        printf("\nAdd Data\n");
        printf("\...\n");
        printf("\nExit\n");

        scanf("%d", choice);

        switch (choice) {
        
        case1: 
            break;
        case2: 
            break;
        case3:
            break;
        default: printf("wrong choice.Enter Again");
            break;
        }

    }
    while(choice !=3);

    }
    */