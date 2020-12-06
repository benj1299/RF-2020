#pragma once

typedef struct Matrix Matrix;
struct Matrix {

    unsigned int nrows;
    unsigned int ncols;
    double* data;
    double* distance;
};

void _swap_data_distance_matrix(Matrix *m, int i);

void fill_data_in_matrix (char* path, Matrix *matrice);

Matrix* init_matrix(unsigned int nrows, unsigned int ncols);
double get_matrix_value(Matrix* matrix, unsigned int row, unsigned int col);
double* get_matrix_row(Matrix* matrix, unsigned int row);
void set_matrix_value(Matrix* matrix, unsigned int row, unsigned int col, double val);
void delete_matrix(Matrix** m);
void print_all_matrix(Matrix *m);
void sort_matrix(Matrix *m);
void fulfill_matrix(Matrix *m, const char* path);
int _list_files_in_dir(const char* path, char *data[]);

double lp_norm(Matrix *matrix_base, double* new_point, unsigned int dim);

void copy_row (Matrix* head, Matrix* matrice , unsigned int nb_kluster, unsigned int row);
void copy_matrice_tab (Matrix* head, double* tab, unsigned int size, unsigned int row);
void copy_tab (double* head, double* tab, unsigned int size);
void copy_tab_int (int* head, int* tab , unsigned int size);
double lowest_value_indice (double* tab, unsigned int size);
int do_stop (unsigned int* head, unsigned int* tab, unsigned int size);
void calc_centroid (unsigned int* classified,unsigned int size ,Matrix* centroid, Matrix* base,unsigned int nb_cluster);
void classifier(Matrix* centroid, Matrix* base , unsigned int* classified);
void _init_tab_zero (double* tab, unsigned int size);
void _init_tab_zero_int (unsigned int* tab, unsigned int size);
void _devide_tab(double* tab, unsigned int size, double dividente);