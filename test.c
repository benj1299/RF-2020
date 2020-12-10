#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h> 
#include <errno.h>
#include "utils.h"
#include "classifier.h"

/*
    Effectue un cross validation pour KNN et revoies son taux d'erreur (pourcentage de réponse véridique de l'algorithme)
*/
double cross_validation_knn(Matrix* matrix, int k, int dim, int dp, const char* type){
    Matrix* test_dataset[k];
    Matrix* train_dataset = NULL;
    double* result = NULL;
    double euclidean_distance = 0;
    double true_result = 0;
    double false_result = 0;
    double count = 0;

    int confusion_matrix[matrix->nclass][matrix->nclass];
    for (int i= 0; i < matrix->nclass; i++)
        _init_tab_zero((double*)confusion_matrix[i], matrix->nclass);

    // Créé une copie du dataset
    Matrix* m = init_matrix(matrix->nrows, matrix->ncols);
    copy_matrix(matrix, m);

    // Mélange aléatoirement les données du dataset m
    shuffle_matrix(m);

    // Sépare le dataset en k group dans test_dataset
    cut_matrix(m, k, test_dataset);

    for(int i=0; i < k; i++){
        // Créé une copie du dataset
        train_dataset = init_matrix(m->nrows, m->ncols);
        copy_matrix(m, train_dataset);

        // Construit le train_dataset en supprimant les données de test_dataset de la copie
        delete_zone_matrix(train_dataset, i, k);

        // Entrainement du modèle test
        for (int j = 0; j < test_dataset[i]->nrows; j++){
            count++;
            
            // Si régression, renvoyer la moyenne de chaque colonne des k éléments.
            if (strcmp("regression", type) == 0){
                result = knn_supervised_regression(train_dataset, test_dataset[i]->data[j], dim, dp);
                // Evaluation du modele de test
                euclidean_distance = lp_norm(train_dataset, result, 2);
                // Conserver le score
            }

            // Si classification, renvoyer le label qui est le plus apparu.
            else if(strcmp("classification", type) == 0){
                char* res = knn_supervised_classification(train_dataset, test_dataset[i]->data[j], dim, dp);
                // Evaluation du modele de test
                printf("res : %s | test : %s\n", res, test_dataset[i]->class[j]);
                
                // On ajoute le résultat à la matrice de confusion
                ++confusion_matrix[get_number(test_dataset[i]->class[j])-1][get_number(res)-1];
            }

            else {
                printf("Erreur KNN : Type non reconnu");
            }
        
        }
        // Supprime le modèle
        delete_matrix(train_dataset);
    }

    // Supprime la matrice copiée m
    delete_matrix(m);
    
    if(strcmp("classification", type) == 0){
        for (int i = 0; i < matrix->nclass; i++){
            printf("-----------------------------------\n");
            for (int j = 0; j < matrix->nclass; j++){
                printf("| %d ", confusion_matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        if(count>0)
            return count;
        return 0;
    }

    else {
        printf("Erreur KNN : Type non reconnu");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
    Base représente les datas d'entrainement de KNN
    test représente le jeu de données tests appartenant à une meme classe
    k le nombre de k-NN
    dp la distance power pour le calcule des distances de KNN

    Renvoies la matrice de confusion des données
void confusion_matrix(Matrix* base, Matrix* test, int k, int dp){
    int true_positive = 0;
    int false_negative = 0;


    for (int i = 0; i < m->nrows; i++){
        for(int j = 0; j < m->ncols; j++){
            char* res = knn_supervised_classification(base, test->data[i], k, dp);
            if(strcmp(res, test->class[i]) == 0)
                true_positive++;
            else
                false_negative++;
        }
    }
}
*/
