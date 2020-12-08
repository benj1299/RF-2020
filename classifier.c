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
    Renvoies l'index de la classe de new_point
*/
void knn_supervised(Matrix *m, char* new_point, int k, int distance_power, const char* type) {
    int result, count = 0;
    double *reg, *new_point_num = malloc(m->ncols * sizeof(double));
    int* freq = malloc(m->nclass*sizeof(int));
    for(int i=0; i < m->nclass; i++)
        freq[i] = -1;

    // Ajoute au tableau les données du fichier new_point
    add_new_point(new_point, new_point_num);

    // Calcule les distances entre new_point et la matrice 
    double minkowski_metric = lp_norm(m, new_point_num , distance_power);

    // Trie la matrice (avec ses classes) et les distances par ordre croissant
    sort_matrix_by_distance(m);

    // Si régression, renvoyer la moyenne de chaque colonne des k éléments.
    if (strcmp("regression", type) == 0){
        printf("Résultat : \n");

        for(int col=0; col < m->ncols; col++){
            for(int row=0; row < k; row++){
                reg[col] += get_matrix_row(m, row)[col];
            }
            
            if(reg[col] != 0){
                reg[col] /= m->ncols;
                printf("Colonne %d : %lf\n", col, reg[col]);
            }
        }
    }

    // Si classification, renvoyer le label qui est le plus apparu.
    else if(strcmp("classification", type) == 0){
        // Si la distance est à 0 alors le point appartient à la classe correspondant au point de la base de données
        if (m->distance[0] == 0){
            printf("Le nouveau point a pour classe : %s\n", m->class[0]);
            exit(EXIT_SUCCESS);
        }

        // Compte la fréquence d'apparation des classes pour les k premiers élements de la liste
        for(int i=0; i < k; i++){
            count = 1;
            for(int j=i+1; j < k; j++){
                if(strcmp(m->class[i], m->class[j]) == 0){
                    count++;
                    freq[j] = 0; // Pour ne pas compter les doublons
                }
            }
            if(freq[i] != 0){
                freq[i] = count;
            } 
        }

        // Ajoute à result l'index de la classe qui est apparue le plus souvent
        int init = freq[0];
        for(int i=1; i < k; i++){
            if(fmax(init, freq[i]) != init){
                init = freq[i];
                result = i;
            }
        }

        printf("Resultats : \n");
        printf("Le nouveau point a pour classe : %s\n", m->class[result]);

        for(int i=0; i < k; i++){
            printf("class : %s\n", m->class[i]);
            printf("distance : %lf\n\n", m->distance[i]);
        } 
    }
        
    else {
        printf("Erreur KNN : Type non reconnu");
        exit(EXIT_FAILURE);
    }

      
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
        }else { //Si c'est pas la première fois

            // On calcul les nouveaux centroid
            copy_tab_int(tampon_classified, classified_tab, number_of_item); // On stock l'ancienne valeur de la classification
            calc_centroid(classified_tab,number_of_item,centroid,base, k_cluster);
        }

        classifier(centroid, base, classified_tab); // On classifie avec les centroids
    }while (do_stop(tampon_classified,classified_tab,number_of_item) == 0);
}

double squared_error_partitioning(double image) {    



    return 0;
}