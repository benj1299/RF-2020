#pragma once

double init_knn(Matrix *m, double* new_point, int k, int distance_power);
double* knn_supervised_regression(Matrix *m, double* new_point, int k, int distance_power);
char* knn_supervised_classification(Matrix *m, double* new_point, int k, int distance_power);
void k_means(Matrix* base, unsigned nb_dimension,unsigned int k_cluster,int* classified_tab, unsigned int number_of_item);