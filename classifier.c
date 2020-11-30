#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "classifier.h"

/*
    K-Nearest-Neighbor Classifier
    Principe de K-NN : dis moi qui sont tes voisins, je te dirais qui tu es !
    Inputs : 
        - m Matrice des données correspondantent aux images
        - k : Nombre de voisins K les plus proches à considérer
        - Type de calcule de distance p (Euclidienne, ...)
*/
double knn_supervised(Matrix *m, double* new_point, int k, int distance_power, const char* type) {
    double result = 0;

    double minkowski_metric = lp_norm(m, new_point , distance_power);

    sort_matrix(m);

    // Si régression, renvoyer la moyenne des étiquettes K.
    if (strcmp("regression", type) == 0){
        for (int i = 0; i < k; i++){
            result += m->distance[i];
        }
        result /= sizeof(*m->distance)/sizeof(double); 
    }

    // Si classification, renvoyer l'étiquette majoritaire.
    else if(strcmp("classification", type) == 0){
        for (int i = 0; i < k; i++){
            result = fmax(m->distance[i], result);
        }
    }
        
    else {
        printf("Erreur KNN : Type non reconnu");
        exit(EXIT_FAILURE);
    }

    // Recupérer le label correspondant à result

    return result;
}

    /*  
        1- On choisi aléatoirement k centre parmit les points de la base

        2- On calcul les distances entres les K-centres et les points

        3- On évalue chaque distance, la distance la plus petite vis a vis d'une class confère l'item à cette class

        4- On Vérifie si les class on changé par rapport à l'itération précédente
            - Si oui on retourne en 2 mais en calculant les moyennes de chaque classes qui deviennent les nouveaux K-centre
            - Si non on stop
    */
int* k_means(Matrix* base, unsigned nb_dimension,unsigned int k_cluster, unsigned int methode) {

    printf("\tInit des matrices \n");

    print_all_matrix(base);

    unsigned int random_point; // Contenir le nombre aléatoire
    Matrix* centroid = init_matrix(k_cluster,base->ncols);// Contenir les centroids
    unsigned int first = 0;

    // Tableau qui contient les classes
    unsigned int classified [16]; // ATTENTION IL FAUT RETIRER LE 99 et mettre à la place k_cluster*nb_item
    unsigned int tampon_classified [16];
    printf("\tInit du tampon de 16 valeurs \n");
    _init_tab_zero(tampon_classified , 16); // On le remplit de 0;

    do {
        printf("\t\t On entre dans l'algo  \n");

        if (first == 0) { // SI on rentre pour la première fois dans la boucle
            printf("\t\tPremière entré dans la boucle\n");
            first = 1;
            // On commence par assigner aléatoirement les k_cluster centroid
            srand(time(NULL));
            for (int cluster = 0 ; cluster < k_cluster ; cluster ++) {

                random_point = rand()%k_cluster;

                copy_row(centroid,base,cluster,random_point);
            }
        }else { // Si c'est pas la première fois

            // On calcul les nouveaux centroid
            copy_tab_int(tampon_classified, classified, 16); // On stock l'ancienne valeur de la classification
            printf("2\n");
            /*calc_centroid(classified,16,centroid,base, k_cluster);
            printf("coucou");*/
        }

        classifier(centroid,base,classified); // On classifie avec les centroids


    }while (do_stop(tampon_classified,classified,16)==0);

    return classified;
}


double squared_error_partitioning(double image) {    



    return 0;
}