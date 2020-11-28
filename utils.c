#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h> 
#include "utils.h"

/*
    ---------------------------------------------------------------------------------------------------------------
    Ce fichier contient toutes les structures et fonctions permettant de récolter et traiter les données du système
    ---------------------------------------------------------------------------------------------------------------
*/

/*
    Permet d'initialiser une matrice avec un nombre de lignes (nrows) et de colonne (ncols) affecté en paramètre
    Chaque correspond à toute les données d'une caractéristique
*/
Matrix* init_matrix(unsigned int nrows, unsigned int ncols) 
{
    Matrix *m = NULL;
    m = malloc(sizeof(Matrix));

    if (!m) {
        printf("Erreur de malloc pour la creation de la matrice d'utils.c");
    }

    m->data = NULL;
    m->data = (double *)malloc(nrows * ncols * sizeof(double));
    m->distance = (double *)malloc(nrows * ncols * sizeof(double));


    if (!m->data || !m->distance) { 
        printf("Erreur d'affectation de données pour la creation de la matrice d'utils.c");
    }

    m->nrows = nrows;
    m->ncols = ncols;

    return m;
}

/*
    Permet d'afficher toutes les données d'une matrice
*/
void print_all_matrix(Matrix *m){
    double count = 0; 
    for (int i = 0; i <  m->nrows; i++) {
      for (int j = 0; j < m->ncols; j++){
          printf("%f\n", *(m->data + i*m->ncols + j));
      }
    }
}

/*
    Permet de récupérer la donnée présente à la position ("row", "col") de la matrice "matrix" fournit en paramètre
*/
double get_matrix_value(Matrix* matrix, unsigned int row, unsigned int col) 
{
    return *(matrix->data + row * matrix->ncols + col);
}

/*
    TODO : Il faut renvoyer seulement un point (un ligne)

*/
double* get_matrix_row(Matrix* matrix, unsigned int row) {

    return (matrix->data+row);
}

/*
    Permet d'ajouter la valeur "val" dans la matrice "matrix" à la position ("row", "col")
*/
void set_matrix_value(Matrix* matrix, unsigned int row, unsigned int col, double val) 
{
    *(matrix->data + row*matrix->ncols + col) = val;
}

/*
    Permet de libérer la mémoire d'une matrice "m"
*/
void delete_matrix(Matrix** m)  {
    free(*m);
}

/*
    Trie par ordre croissant le tableau des distances et des données de la matrice m via un tri un à bulle
    permettant d'associer chaque distance à sa coordonnée après tri

*/
void sort_matrix(Matrix *m)  { 
   int i, j;
   int n = sizeof(*m->distance)/sizeof(double);

   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (m->distance[j] > m->distance[j+1])
              _swap_data_distance_matrix(m, j);
}

/*
    Rempli la matrice m avec les données présentes dans path
    
    Inputs : 
        - Matrice m
        - Chemin de données path
*/
void fulfill_matrix(Matrix *m, const char* path) {
    char *data[] = {};
    int elements = _list_files_in_dir(path, data);
    FILE *fp;
    char buff[50000];

    for (int i = 0; i < elements; i++){
        if((fp = fopen(data[i], "r")) == NULL){
            printf("Erreur : Le fichier %s n'a pas pu être ouvert", data[i]);
            exit(EXIT_FAILURE);
        }

        //fscanf(fp, "%[^\n]", buff);
        printf("%d - %s: \n", i, data[i]);
        fclose(fp);
    }
    
}

/*
    Liste les fichiers contenus dans un dossier
*/
int _list_files_in_dir(const char* path, char *data[]){
    
    int i = 0;
    struct dirent *de;  
    DIR *dr = opendir(path); 
    
    if (dr == NULL) { 
        printf("Impossible d'ouvrir le répertoire de données datas/%s", path);
        exit(EXIT_FAILURE); 
    } 
  
    while ((de = readdir(dr)) != NULL){
        data[i] = de->d_name;
        i++;
    }

    closedir(dr);
    return i;
}

/*
    Calcule la LpNorm pour d dimensions et stocke dans matrix->distance les distance de chaque point avec new_point.

    Inputs :
        - matrix correspond à un pointeur de matrice (la première ligne de la matrice représente l'axe x et les lignes suivantes les points correspondants)
        - new_point correspond à la coordonnée à évaluer
        - dim correspond au nombre de dimension 
        (Dim 1 -> La distance de Manhattan)
        (Dim 2 -> La distance Euclidienne)

*/
double lp_norm(Matrix *m, double* new_point, unsigned int dim) { 
    int res = 0;

    for(int i = 0; i < m->nrows; i++){
        for (int j = 0; j < m->ncols; j++){
           m->distance[i] = pow(fabs(get_matrix_value(m, i, j) - new_point[j]), dim);
           res += m->distance[i];
        }
    }

    return pow(res, 1/dim);
}

/*
    Échange les coordonnées d'un point du tableau
*/
void _swap_data_distance_matrix(Matrix *m, int i) { 
    double temp = m->distance[i]; 

    m->distance[i] = m->distance[i+1]; 
    m->distance[i+1] = temp; 

    temp = m->data[i]; 

    m->data[i] = m->data[i+1]; 
    m->data[i+1] = temp; 
} 

void calcul_distance (){

}

void cluster () {

}
int do_stop() {
    
}
/*
    Déclare et relie chaque Matrice (nb_class * nb dimension) avec sa classe.
        
        Inputs : 
            - Tableau devant contenir les pointeurs vers les Matrices
            - La dimensions des items des classes
*/
void init_tab (Matrix** tab,int nb_class,int nb_dimension) {

    for (int i = 0 ; i < nb_class; i++) {
        *(tab+i) = init_matrix(nb_dimension,nb_class);
    }
}