#pragma once

typedef struct Matrix Matrix;
struct Matrix {
    unsigned int nrows;
    unsigned int ncols;
    unsigned int nclass;
    double** data;
    double* distance;
    char* class[500];
};

void _swap_data_matrix(Matrix *m, int i);

void fill_data_in_matrix (char* path, Matrix *matrice);

Matrix* init_matrix(unsigned int nrows, unsigned int ncols);
double get_matrix_value(Matrix* matrix, unsigned int row, unsigned int col);
double* get_matrix_row(Matrix* matrix, unsigned int row);
void set_matrix_value(Matrix* matrix, unsigned int row, unsigned int col, double val);
void delete_matrix(Matrix* m);
void print_all_matrix(Matrix *m);
void sort_matrix_by_distance(Matrix *m);
void shuffle_matrix(Matrix* m);
void fulfill_matrix(Matrix *m, char* path);
void copy_matrix(Matrix *m, Matrix *m2);
void cut_matrix(Matrix* m, int k, Matrix** arr);
void delete_zone_matrix(Matrix* m, int i, int k);

void _count_dim_file(const char* path, int *nrows, int *ncols);
int _list_files_in_dir(char* path, char *data[]);
void add_new_point(char* new_point, double* new_point_num);

double lp_norm(Matrix *matrix_base, double* new_point, unsigned int dim);

Matrix* load_data (Matrix *matrice, char *path, int *nrows, int *ncol);

void write_in_file(int* data,char* path,unsigned int size);

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
int get_number(char* str);