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

void k_means(Matrix** base, int nb_class, int nb_item , int k_cluster, int method) {

    /*
    
        1- On choisi aléatoirement k centre parmit les points de la base

        2- On calcul les distances entres les K-centres et les points

        3- On évalue chaque distance, la distance la plus petite vis a vis d'une class confère l'item à cette class

        4- On Vérifie si les class on changé par rapport à l'itération précédente
            - Si oui on retourne en 2 mais en calculant les moyennes de chaque classes qui deviennent les nouveaux K-centre
            - Si non on stop
    */



   srand(time(NULL));

   int rand_class,rand_item;// Les nombres aléatoires qui vont choisir les points
   double* centers [k_cluster];// Tableau qui va contenir les centres 

   for (int i = 0; i < k_cluster; i ++) { // On assigne les K centres dans le tableau

       rand_class = rand()%nb_class;
       rand_item = rand()%nb_item;

       centers[i] = get_matrix_row(base,rand_item);
   }


   do {

       // on calcul les distances euclédiennes
       calcul_distance ();

       // On classifie
       cluster();

   }while(do_stop());
}


double squared_error_partitioning(double image) {    



    return 0;
}