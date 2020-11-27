#pragma once

typedef struct Matrix Matrix;
struct Matrix
{
    uint32_t nrows;
    uint32_t ncols;
    double* data;
    double* distance;
};

void _swap_data_distance_matrix(Matrix *m, int i);

Matrix* init_matrix(uint32_t nrows, uint32_t ncols);
double get_matrix_value(Matrix* matrix, uint32_t row, uint32_t col);
void set_matrix_value(Matrix* matrix, uint32_t row, uint32_t col, double val);
void delete_matrix(Matrix** m);
void print_all_matrix(Matrix *m);
void sort_matrix(Matrix *m);
void fulfill_matrix(Matrix *m, const char* path);
int _list_files_in_dir(const char* path, char *data[]);

double lp_norm(Matrix *matrix_base, double* new_point, uint32_t dim);
