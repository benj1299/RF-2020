#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"

#define NB_CLASS 9
#define NB_ITEM 11

// Matrice 9 * 11 


int main(int argc, char *argv[]) {


    //Tab qui représente les données à classifier
    Matrix* base [NB_CLASS];
    int dimension = 16; // Pour le E34 il y a 16 valeurs

    //En fonction de la méthode de traitement utilisé on va déclarer des tailles de matrice différentes
    init_tab(base,NB_CLASS,dimension);

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