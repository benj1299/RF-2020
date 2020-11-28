#pragma once

typedef struct Matrix Matrix;
struct Matrix {

    unsigned int nrows;
    unsigned int ncols;
    double* data;
    double* distance;
};

void _swap_data_distance_matrix(Matrix *m, int i);

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

void init_tab (Matrix** tab,int nb_class, int nb_dimension);
void calcul_distance ();
void cluster ();
int do_stop();

