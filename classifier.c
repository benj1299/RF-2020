#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "classifier.h"
#include <time.h> 

/*
    K-Nearest-Neighbor Classifier
    Principe de K-NN : dis moi qui sont tes voisins, je te dirais qui tu es !
    Inputs : 
        - m Matrice des données correspondantent aux images
        - k : Nombre de voisins K les plus proches à considérer
        - Type de calcule de distance p (Euclidienne, ...)
    Renvoies un tableau contenant les resultats
*/
double* knn_supervised(Matrix *m, double* new_point, int k, int distance_power, const char* type, double *result) {
    
    // Calcule les distances entre new_point et la matrice 
    double minkowski_metric = lp_norm(m, new_point , distance_power);

    // Trie la matrice et les distances par ordre croissant
    sort_matrix_by_distance(m);

    // Si régression, renvoyer la moyenne des étiquettes K.
    if (strcmp("regression", type) == 0){
        for(int i=0; i < m->ncols; i++){
            for(int j=0; j < k; j++)
                result[i] += get_matrix_row(m, j)[i];
            
            if(result[i] != 0)
                result[i] /= m->ncols;
        }
    }

    // Si classification, renvoyer l'étiquette majoritaire.
    else if(strcmp("classification", type) == 0){
        // j'ai eu un prb de conception à refaire
    }
        
    else {
        printf("Erreur KNN : Type non reconnu");
        exit(EXIT_FAILURE);
    }

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
void k_means(Matrix* base, unsigned nb_dimension, unsigned int k_cluster, int* classified_tab, unsigned int number_of_item) {

    Matrix* centroid = init_matrix(k_cluster,base->ncols);// Contenir les centroids
    unsigned int first = 0;

    unsigned int tampon_classified [number_of_item];// Le tempon qui va contenir les items classifiées de l'itération n-1
    _init_tab_zero_int(tampon_classified , number_of_item); // On le remplit de 0;
    _init_tab_zero_int(classified_tab, number_of_item);// On le remplit de 0;

    do {
        if (first == 0) { // SI on rentre pour la première fois dans la boucle
            first = 1;
            // On commence par assigner aléatoirement les k_cluster centroid
            srand(time(NULL));

            unsigned int random_point; // Contenir le nombre aléatoire

            for (int cluster = 0 ; cluster < k_cluster ; cluster ++) {

                random_point = rand()%k_cluster;

                copy_row(centroid,base,cluster,random_point);
            }
        }else { // Si c'est pas la première fois

            // On calcul les nouveaux centroid
            copy_tab_int(tampon_classified, classified_tab, number_of_item); // On stock l'ancienne valeur de la classification
            calc_centroid(classified_tab,number_of_item,centroid,base, k_cluster);
        }

        classifier(centroid, base, classified_tab); // On classifie avec les centroids
    }while (do_stop(tampon_classified,classified_tab,number_of_item)==0);

}

double squared_error_partitioning(double image) {    



    return 0;
}