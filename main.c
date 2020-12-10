#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "classifier.h"
#include "test.h"


int main(int argc, char *argv[]) {
    
    int choice, nrows, ncols, file_writting;
    char* path = "data.kmean"; // Fichier par défault crée
    double cross_res;

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

    // Test de validation croisée
    int i = 5;
    printf("Taux d'erreur de KNN pour k = %d pour la classification : %lf%%\n", i, cross_validation_knn(m, 9, i, 2, "classification"));
    
    //KNN Variables
    int k, pd, type, result = 0;
    char new_point[100];
    double* new_point_num;

    printf("Menu\n\n 1 - KNN\n 2 - Kmeans\n 3 - Sortir du programme\n\nEntrez votre choix : ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("\tVeuillez choisir le nombre de plus proche voisins : ");
            scanf("\t%d",&k);
            printf("\tVeuillez choisir la puissance à utiliser pour le calcule de distance (Ex : 2 = Euclidean Distance) : ");
            scanf("\t%d",&pd);
            printf("\tVeuillez choisir un type, (1) regression ou (2) classification : ");
            scanf("\t%d", &type);
            printf("\tVeuillez choisir le chemin du point à comparer : ");
            scanf("\t%100s", new_point);

            add_new_point(new_point, new_point_num);

            if(type == 1)
                knn_supervised_regression(m, new_point_num, k, pd);
            else if(type == 2)
                printf("Le point appartient à : %s\n", knn_supervised_classification(m, new_point_num, k, pd));
            else {
                printf("Erreur KNN : Type non reconnu");
            }

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
            printf("Merci de votre visite. \n");
            break;
    }
    
    delete_matrix(m);

    return EXIT_SUCCESS;
}