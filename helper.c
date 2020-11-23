#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "helper.h"


/*
    K-Nearest-Neighbor Classifier
    Principe de K-NN : dis moi qui sont tes voisins, je te dirais qui tu es !
    Inputs : 
        - Ensemble de données datas
        - Nombre de voisins K les plus proches à considérer
        - Type de calcule de distance d
*/
double knn_supervised(double datas, int k, int d) {    
    /*

    1) Pour chaque donnée dans la base d'apprentissage

        a) Calculez la distance entre l'inconnu et la donnée courante.

        b) Mémoriser cette distance et la donnée associée dans une liste de couple (distance, donnée).

    2) Triez la liste distance_Donnée du plus petit au plus grand sur les distances.

    3) Choisissez les k premières entrées de cette liste.

    4) Obtenir les étiquettes des k données de la base d'apprentissage sélectionnées.

    5) Si régression, renvoyer la moyenne des étiquettes K.

    6) Si classification, renvoyer l'étiquette majoritaire.

    */
    return 0;
}

double k_means(double image) {    
    return 0;
}

double squared_error_partitioning(double image) {    
    return 0;
}
