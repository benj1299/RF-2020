#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    int r = 0;
    int c = 0;
    struct Matrix m = matrix_create(80, 24);

    for (r=0; r < m.height; ++r)
    {
        int* row = matrix_row(&m, r);
        for (c=0; c < m.width; ++c)
            row[c] = r * m.width + c;
    }
    matrix_destroy(&m);
    return EXIT_SUCCESS;
}