#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"


int main(int argc, char *argv[]) {
    
    int choice, nrows, ncols, file_writting;
    char* path = "data.kmean"; // Fichier par défault crée

    if (argc < 2) {
        // Exemple ./output ./datas/F0/
        perror("Data path manquant \n");
        return EXIT_FAILURE;
    }

    if (argc >=3)
        path = argv[2]; 

    _count_dim_file(argv[1], &nrows, &ncols);

    int classified [nrows];
    int nombre_cluster = 2;

    Matrix* m = init_matrix(nrows, ncols);
    fulfill_matrix(m, argv[1]);
    
    //KNN Variables
    double* result, *new_point = malloc(ncols * sizeof(double));
    int k, pd, type = 0;

    printf("Menu\n\n Entrez votre choix : ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("\tVeuillez choisir le nombre de plus proche voisins : ");
            scanf("\t%d",&k);
            printf("\tVeuillez choisir la puissance à utiliser pour le calcule de distance (Ex : 2 = Euclidean Distance) : ");
            scanf("\t%d",&pd);
            printf("\tVeuillez choisir un type, (1) regression ou (2) classification : ");
            scanf("\t%d", &type);

            if(type == 1)
                knn_supervised(m, new_point, k, pd, "regression", result);
            else
                knn_supervised(m, new_point, k, pd, "classification", result);

            printf("Result :\n");
            for (int i = 0; i < ncols; i++)
                printf("L'élément : %d a pour valeur : %lf\n", i, result[i]);

            break;

        case 2: 
            printf("\tVeuillez choisir le nombre de cluster : \n");
            scanf("\t%d",&nombre_cluster);
            k_means(m, ncols, nombre_cluster, classified, nrows);

            //On demande si on veut écrire les données dans un fichier
            printf("\t Voulez vous écrire les donnés dans un fichier ? \n");
            printf("\t\t1-oui  2-non\n");
            scanf("%d",&file_writting);

            if (file_writting == 1) {
               write_in_file(classified,path,nrows);
            }else{
                // On les affiches dans la console
                for (int i = 0 ; i < nrows; i++) {
                    printf ("l'élément %d fait partie de la classe : %d \n", i+1, classified[i]+1);
                }
            }
            break;
        
        default: 
            printf("Ce choix n'existe pas. Veuillez en choisir un autre. \n");
            break;
    }
    

    delete_matrix(m);

    return EXIT_SUCCESS;
}