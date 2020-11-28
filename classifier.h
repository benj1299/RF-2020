#pragma once

double knn_supervised(Matrix *m, double* new_point, int k, int distance_power, const char* type);
void k_means(Matrix** base, int nb_class, int nb_item , int k_cluster, int methode);
double squared_error_partitioning(double image);