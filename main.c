#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "pgm.h"

int main(int argc, char *argv[])
{
    uint32_t row = 10;
    uint32_t column = 10;
    double val = 0; 

    Matrix *m = init_matrix(row, column);

    //printf("%d", pgm_file->width);

/*
    char choice;
    do {
        printf("Menu\n\n");
        printf("\nAdd Data\n");
        printf("\...\n");
        printf("\nExit\n");

        scanf("%d", choice);

        switch (choice) {
        
        case1: 
            break;
        case2: 
            break;
        case3:
            break;
        default: printf("wrong choice.Enter Again");
            break;
        }

    }
    while(choice !=3);

    }
    */

    return EXIT_SUCCESS;
}