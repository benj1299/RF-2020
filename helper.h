#pragma once

int cmpfunc (const void * a, const void * b);
double knn_supervised(Matrix *m, int k, int d, int type);
double k_means(double image);
double squared_error_partitioning(double image);