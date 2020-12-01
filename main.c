#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"

#define NB_ITEM 8
#define NB_CLUSTER 2

// Matrice 9 * 11 


int main(int argc, char *argv[]) {

    unsigned int nb_dimension = 2; // J'ai pris 16 psk je teste sur la méthode E34 à 16 valeurs

    double test [8][2] = {{5.6,8.2}, // 8 éléements de deux coordoonées
                           {5.6,7.3},
                           {5.1,7.8},
                           {5.9,8.0},
                           {8.0,10.2},
                           {8.0,12.5},
                           {7.6,10.4},
                           {7.6,10.8},
                           };

    

    // On Initialise la matrice qui va représenter la base
    Matrix* base_apprentissage = init_matrix(NB_ITEM,nb_dimension);
    // On remplie les valeurs de la matrices
    //fulfill_matrix(base_apprentissage,"test.achanger");

    for (int i = 0 ; i < 8; i ++) {
        for (int j = 0; j < 2 ; j++) {
            set_matrix_value(base_apprentissage,i,j,test[i][j]);
        }
    }

    printf("\n");
    printf("On lance l'algorithme K-Mean avec la base de connaissance \n");
    unsigned int classified [16];
    k_means(base_apprentissage,nb_dimension,NB_CLUSTER,classified);

    free(base_apprentissage);

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