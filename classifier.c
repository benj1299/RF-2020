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

double k_means(double image) {    
    return 0;
}

double squared_error_partitioning(double image) {    
    return 0;
}