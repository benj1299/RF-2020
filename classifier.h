#pragma once

double knn_supervised(Matrix *m, double* new_point, int k, int distance_power, const char* type);
double k_means(double image);
double squared_error_partitioning(double image);