#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h> 
#include <errno.h>
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
Matrix* init_matrix(unsigned int nrows, unsigned int ncols) {
    Matrix *m = NULL;
    m = malloc(sizeof(Matrix));

    if (!m) {
        printf("Erreur de malloc pour la creation de la matrice d'utils.c");
        exit(EXIT_FAILURE);
    }

    m->data = (double**) malloc(nrows*sizeof(double*));
    m->distance = (double*)malloc(nrows * ncols * sizeof(double));
    
    for (int i = 0; i < nrows; i++)
        m->data[i] = (double*) malloc(ncols*sizeof(double));

    if (!m->data || !m->distance) { 
        printf("Erreur d'affectation de données pour la creation de la matrice d'utils.c");
        exit(EXIT_FAILURE);
    }

    m->nrows = nrows;
    m->ncols = ncols;

    return m;
}

/*
    Récupère toutes les données et les charges dans la matrice matrice
*/
void fill_data_in_matrix(char* path, Matrix *matrice) {

    struct dirent *dir;
    // Il faut que matrice soit instancier dans cette fonction pour avoir les dimensions des données 

    DIR *directeur = opendir(path); // On ouvre le dossier qui possède tous les fichiers contenant les données.

    if (directeur) {

        while ((dir = readdir(directeur)) != NULL) { // On ouvre chaque fichier du
            if ( strcmp(dir->d_name,"..")!=0 || strcmp(dir->d_name,".") !=1 ){ // Si les chaines de caractères sont différentes d . et ..

                printf("%s \n",dir->d_name);
                //On ouvre le fichier de nom dir->d_name
                
            }
            
        }
        closedir(directeur);
    }
}

/*
    Permet d'afficher toutes les données d'une matrice
*/
void print_all_matrix(Matrix *m) {
    for (int i = 0; i <  m->nrows; i++)
      for (int j = 0; j < m->ncols; j++)
          printf("%f\n", get_matrix_value(m, i, j));
}

/*
    Permet de récupérer la donnée présente à la position ("row", "col") de la matrice "matrix" fournit en paramètre
*/
double get_matrix_value(Matrix* matrix, unsigned int row, unsigned int col) 
{
    return matrix->data[row][col];
}

/*
    Permet d'ajouter la valeur "val" dans la matrice "matrix" à la position ("row", "col")
*/
void set_matrix_value(Matrix* matrix, unsigned int row, unsigned int col, double val) {
    matrix->data[row][col] = val;
}

/*
    TODO : Il faut renvoyer seulement un point (un ligne)
    A revérifier

*/
double* get_matrix_row(Matrix* matrix, unsigned int row) {
    return matrix->data[row];
}

/*
    Calcul le nombre d'items
    Le -2 correspond au dossier '.' et '..'
*/
int calc_items(char* path_data) {

    DIR *d;
    struct dirent *dir;
    int compteur  = 0;

    d = opendir(path_data);

    if (d) {

        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
            compteur ++;
        }

    closedir(d);
  }

  return compteur-2;
}

/*
    Permet de libérer la mémoire d'une matrice "m"
*/
void delete_matrix(Matrix* m)  {
    free(m);
}

/*
    Trie par ordre croissant le tableau des distances et des données de la matrice m via un tri un à bulle
    permettant d'associer chaque distance à sa coordonnée après tri

*/
void sort_matrix_by_distance(Matrix *m)  { 
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
    char *data[m->nrows];
    FILE *fp;
    extern int errno;
    int j = 0;
    double element_value;

    // Créer une variable intermédiaire car _list_files_in_dir supprime path lors de son appel
    char *cp_path = malloc(strlen(path) + 1);
    strcpy(cp_path, path);

    int elements = _list_files_in_dir(path, data);
    
    for (int i = 0; i < elements; i++){
        j = 0;
        char *result = malloc(strlen(cp_path) + strlen(data[i]) + 1);
        strcpy(result, cp_path);
        strcat(result, data[i]);

        if((fp = fopen(result, "r")) == NULL){     
            printf("Erreur du fichier %s : %s\n", result, strerror(errno));
        }        
        else {
            while(fscanf(fp, "%lf\n", &element_value) != EOF ) {
                set_matrix_value(m, i, j, element_value);
                //printf("element %d %d : %lf\n", i, j, get_matrix_value(m, i, j));
                j++;
            }
            fclose(fp);
        }
        free(result);
    }
}

/*
    Compte le nombre fichiers et d'elements dans un fichier et le remplit respectivement dans nrows et ncols
*/
void _count_dim_file(const char* path, int *nrows, int *ncols){
    
    struct dirent *de;  
    char c;
    FILE *fp;
    DIR *dr = opendir(path); 
    
    *nrows = 0;
    *ncols = 0;

    if (dr == NULL) { 
        printf("Impossible d'ouvrir le répertoire de données datas/%s", path);
        exit(EXIT_FAILURE); 
    } 
    while ((de = readdir(dr)) != NULL){
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
            if ((*nrows) == 1){
                char *result = malloc(strlen(path) + strlen(de->d_name) + 1);
                strcpy(result, path);
                strcat(result, de->d_name);

                if((fp = fopen(result, "r")) == NULL){     
                    printf("Erreur du fichier %s : %s\n", result, strerror(errno));
                } 
                else {
                    for (c = getc(fp); c != EOF; c = getc(fp)) 
                        if (c == '\n') {
                            (*ncols)++;
                        }
                    fclose(fp);
                }
            }
            (*nrows)++;
        }
    }

    if (closedir(dr) == -1)
        exit(-1);
}

/*
    Liste les fichiers dans "data" contenus dans la dossier "path"
    Renvoi le nombre d'éléments
*/
int _list_files_in_dir(const char* path, char *data[]){
    int i = 0;
    extern int errno;
    struct dirent *de;  
    DIR *dr = opendir(path); 
    
    if (dr == NULL) { 
        printf("Erreur du dossier %s : %s\n", path, strerror(errno));
        exit(EXIT_FAILURE); 
    } 
    while ((de = readdir(dr)) != NULL){
        
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
            data[i] = de->d_name;
            i++;
        }
    }

    if (closedir(dr) == -1)
        exit(-1);
    
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

    double *temp2 = m->data[i]; 

    m->data[i] = m->data[i+1]; 
    m->data[i+1] = temp2; 
} 

/*
    Copy tab dans une row de head 
*/
void copy_matrice_tab (Matrix* head, double* tab, unsigned int size, unsigned int row) {

    for (int i = 0 ; i < size ; i ++) {
        set_matrix_value(head,row,i,tab[i]);
    }
}

/*
    Copie tab dans le head
*/
void copy_tab (double* head, double* tab , unsigned int size){

    printf("1");

    for (int i = 0 ; i < size; i++) {
        head[i] = tab[i];
    }
}

void copy_tab_int (int* head, int* tab , unsigned int size){

    for (int i = 0 ; i < size; i++) {
        head[i] = tab[i];
    }
}

/*
    Copie la ligne row de matrice dans la matrice head
*/
void copy_row (Matrix* head, Matrix* matrice , unsigned int nb_kluster, unsigned int row){

    for (int i = 0; i < head->ncols; i++) {
        set_matrix_value(head,nb_kluster,i,get_matrix_value(matrice,row,i));
    }
}

/*
    Vérifie si les deux tableaux on les mêmes valeurs.
    Renvoie 1 si oui , 0 sinon.

    args :
            Le tableau contenant les valeurs à tester
            Le tableau de référence.
            La taille des tableaux
*/
int do_stop (unsigned int* head, unsigned int* tab, unsigned int size){

    for (int i = 0; i < size ; i ++) {
        printf(".");
        if(head[i] != tab[i]) {
            printf("\n");
            return 0;
        } // S'il y a une différence on stop l'algo et on renvoie 0
    }

    return 1; // Si toutes les valeurs sont les mêmes, on renvoie 1
}

/*
    Divise l'ensemble des valeurs du tableau par le dividente
*/
void _devide_tab(double* tab, unsigned int size, double dividente) {

    for (int i = 0 ; i < size ; dividente ++) {
        tab[i]/=dividente;
    }
}

/*
    Initialise le tabluea avec des 0

    args : 
            -Tableau à initialiser
            -Taille du Tableau
*/
void _init_tab_zero (double* tab, unsigned int size) {
    for (int i = 0 ; i < size ; i ++) {
        tab [i] = 0;
    }
}

void _init_tab_zero_int (unsigned int* tab, unsigned int size) {
    for (int i = 0 ; i < size ; i ++) {
        tab [i] = 0;
    }
}

/*

    Renvoie l'indice de la plus petite valeur du tableau

    args:
         -Tableau dans lequel nous devons trouver la plus petit valeur
         -La taille du tableau
*/
double lowest_value_indice (double* tab , unsigned int size) {

    double value = -1;

    for (int i = 0 ; i < (size-1) ; i ++) {

        if (tab[i] <= tab[i+1])
            value = i;
        else 
            value = i+1;
    }

    return value;
}

/*
    Calcul les nouveaux centroids.

    args:
            Le tableau des items classifiés
            La taille du tableau classifiés
            La matrice contenant les centroids précédents
            La matrice contenant la base d'apprentissage
*/
void calc_centroid (unsigned int* classified,unsigned int size, Matrix* centroid, Matrix* base, unsigned int nb_cluster) {

    //On calcul le mean pour faire les centroids

    for (int cluster = 0 ; cluster < nb_cluster ; cluster ++) {// Pour chaque cluster
        printf("p");
        unsigned int indice = centroid->ncols; 
        double tampon [indice];
        double mean_class [nb_cluster];
        int compteur;

        for (int i = 0; i < base->nrows; i ++) {

            _init_tab_zero(tampon,indice);
            compteur = 0;

            if (classified[i] == cluster) {// Si l'item appartient au cluster en question
                for (int y = 0 ; y < centroid->ncols ; y ++) {// On additionne 
                    tampon[y]+= get_matrix_value(base,i,y);
                    compteur ++;
                }
            }
        }

        //_devide_tab(tampon,indice,compteur);
        //copy_matrice_tab(centroid,tampon,centroid->ncols,cluster); // On ecrit le nouveau centroid dans le tableau du centroid
    }
}

/*
    Prend la base de connaissance et classifie dans classified
*/
void classifier(Matrix* centroid, Matrix* base , unsigned int* classified) {

    // classified est un tableau de Nb_cols

    unsigned int indice = centroid->nrows;
    double tampon_value[indice];

    // On calcul la distance de chaque item par rapport aux centroids.

    for (int i = 0 ; i < base->nrows; i ++) { // Pour chaque item de la base
        for (int cent = 0 ; cent < centroid->nrows; cent++) { // On récupère chaque centroids
            
            double resultat = 0;

            for (int cent_col = 0; cent_col < centroid->ncols ; cent_col ++) { // On récupère chaque valeur
                resultat += pow(get_matrix_value(base,i,cent_col)-get_matrix_value(centroid,cent,cent_col),2);  
            }

            tampon_value[cent] = sqrt(resultat); // On remplit le tempon des distances.
        }

        classified[i] = lowest_value_indice(tampon_value,indice); // On classifie le premier item
    }
}