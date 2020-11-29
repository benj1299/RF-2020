#pragma once

double knn_supervised(Matrix *m, double* new_point, int k, int distance_power, const char* type);
int* k_means(Matrix* base, unsigned nb_dimension,unsigned int k_cluster, unsigned int methode);
double squared_error_partitioning(double image);