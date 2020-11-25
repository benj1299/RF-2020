#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "helper.h"

int cmpfunc (const void * a, const void * b) {
   return (*(double*)a - *(double*)b );
}

/*
    K-Nearest-Neighbor Classifier
    Principe de K-NN : dis moi qui sont tes voisins, je te dirais qui tu es !
    Inputs : 
        - Ensemble de données datas
        - Nombre de voisins K les plus proches à considérer
        - Type de calcule de distance d
*/
double knn_supervised(Matrix *m, int k, int d, int type) {    
    double res = lp_norm(m, d);
    size_t matrix_tall = sizeof(m->distance);
    double result = 0;

    qsort(m->distance, matrix_tall, sizeof(double), cmpfunc);

    // Associer chaque distance à sa coordonnée

    // Si régression, renvoyer la moyenne des étiquettes K.
    if (type == 1){
        for (int i = 0; i < k; i++){
            result += m->distance[i];
        }
        result /= matrix_tall; 
    }

    // Si classification, renvoyer l'étiquette majoritaire.
    else if(type == 2){
        for (int i = 0; i < k; i++){
            result = fmax(m->distance[i], result);
        }
    }
        
    else {
        printf("Erreur KNN : Type non reconnu");
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
