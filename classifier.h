#pragma once

void knn_supervised(Matrix *m, char* new_point, int k, int distance_power, const char* type);
void k_means(Matrix* base, unsigned nb_dimension,unsigned int k_cluster,int* classified_tab, unsigned int number_of_item);
double squared_error_partitioning(double image);