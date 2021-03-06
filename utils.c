#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dirent.h> 
#include <errno.h>
#include <time.h>
#include "utils.h"

/*
    ---------------------------------------------------------------------------------------------------------------
    Ce fichier contient toutes les structures et fonctions permettant de récolter et traiter les données du système
    ---------------------------------------------------------------------------------------------------------------
*/

/*
    Permet d'initialiser une matrice avec un nombre de lignes (nrows) et de colonne (ncols) affecté en paramètre
    Remplit chaque ligne de data à 0
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
    
    for (int i = 0; i < nrows; i++){
        m->data[i] = (double*) malloc(ncols*sizeof(double));
        m->class[i] = malloc(50*sizeof(char));
        for(int j=0; j < ncols; j++)
            m->data[i][j] = 0;
    }

    if (!m->data || !m->distance) { 
        printf("Erreur d'affectation de données pour la creation de la matrice d'utils.c");
        exit(EXIT_FAILURE);
    }

    m->nrows = nrows;
    m->ncols = ncols;

    return m;
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

   for (i = 0; i < m->nrows-1; i++)
       for (j = 0; j < m->nrows-i-1; j++)
           if (m->distance[j] > m->distance[j+1])
              _swap_data_matrix(m, j);
}

/* Permet de générer une permutation aléatoire de la matrice m */
void shuffle_matrix(Matrix* m){
    srand(time(NULL)); 
    for (int i = m->nrows-1; i > 0; i--){ 
        int j = rand() % (i+1); 
       _swap_data_matrix(m, j);
    } 
}

/*
    Coupe la matrice m en k matrice
    Renvoies un tableau de Matrix*
*/
void cut_matrix(Matrix* m, int k, Matrix** arr){
    int matrix_tall = m->nrows/k;
    int count = 0;

    for(int i=0; i < k; i++){
        arr[i] = init_matrix(matrix_tall, m->ncols);
        for(int j=0; j < matrix_tall; j++){
            arr[i]->data[j] = m->data[count+j];
            arr[i]->distance[j] = m->distance[count+j];
            arr[i]->class[j] = m->class[count+j];
        }
        count += matrix_tall;
    }
}

// Supprimer la zone i de la matrice coupée en k séparation
void delete_zone_matrix(Matrix* m, int i, int k){
    int matrix_tall = m->nrows/k;

    for (int c = i*matrix_tall; c < ((i+1)*matrix_tall) - 1; c++){
        m->data[c] = m->data[c+1];
        m->distance[c] = m->distance[c+1];
        m->class[c] = m->class[c+1];
    }
}

/*
    Échange les coordonnées d'un point du tableau avec ses distances et class correspondantes
*/
void _swap_data_matrix(Matrix *m, int i) { 
    double temp = m->distance[i]; 
    double *temp2 = m->data[i]; 
    char *temp3 = m->class[i]; 

    m->distance[i] = m->distance[i+1]; 
    m->distance[i+1] = temp; 

    m->data[i] = m->data[i+1]; 
    m->data[i+1] = temp2; 

    m->class[i] = m->class[i+1]; 
    m->class[i+1] = temp3; 
} 


/*
    Remplit la matrice m avec les données présentes dans path
    
    Inputs : 
        - Matrice m
        - Chemin de données path
*/
void fulfill_matrix(Matrix *m, char* path) {
    char *data[m->nrows];
    FILE *fp = NULL;
    extern int errno;
    int j, size_class = 0;
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
            // Ajout le numero de classe du fichier
            m->class[i][0] = data[i][1];
            m->class[i][1] = data[i][2];
            size_class++;

            while(fscanf(fp, "%lf\n", &element_value) != EOF ) {
                set_matrix_value(m, i, j, element_value);
                //printf("element %d %d : %lf\n", i, j, get_matrix_value(m, i, j));
                j++;
            }
            fclose(fp);
        }
        free(result);
    }
     // Compte le nombre d'éléments distint de m->class
    m->nclass = 1; 
    for (int i = 1; i < size_class; i++) { 
        int j = 0; 
        for (j = 0; j < i; j++) 
            if (strcmp(m->class[i], m->class[j]) == 0) 
                break; 

        if (i == j) 
            m->nclass++; 
    } 
}

/*
    Copie la matrice m1 dans la matrice m2
*/
void copy_matrix(Matrix *m, Matrix *m2){
    for(int i=0; i < m->nrows; i++){
        m2->data[i] = m->data[i];
        m2->distance[i] = m->distance[i];
        m2->class[i] = m->class[i];
    }
}

Matrix* load_data (Matrix *matrice, char *path, int *nrows, int *ncol) {

    _count_dim_file(path , nrows, ncol); // On calcule les dimensions de la matrice 

    printf("%d \n",*nrows);
    printf("%d \n",*ncol);

    matrice = init_matrix(*nrows, *ncol); // On initialise la matrice

    printf("%p \n" , matrice);

    // Pour les boucles qui vont remplir les données
    int compteur_rows = 0;
    int compteur_col = 0;

    char str [500];
    char data_in_file [500]; // pour les données contenues dans les fichiers
    char absolute_path [5000]; //Le chemin du fichier dans le directorie
    char *file_path= path; // Le chemin du dossier

    //Vérification des noms des dossiers
    char* point = ".";
    char* double_point = "..";

    struct dirent *lecture;
    DIR *rep;
    rep = opendir(file_path);

    while ((lecture = readdir(rep))){

        //printf(" %d \n",compteur_rows);

        if (strcmp(lecture->d_name,point)!=0 && strcmp(lecture->d_name,double_point)!=0) { // SI les noms des fichiers ne sont pas '.' et '..'
            // On ouvre le fichier et on lit à l'intérieur

            strcpy(str,lecture->d_name);
            strcpy(absolute_path,file_path);
            strcat(absolute_path,str); // On combine le nom du fichier et le chemin du dossier pour former le chemin


            FILE* fichier = fopen(absolute_path ,"r"); // On ouvre le fichier

            double nombre = 0.0;

            while (fgets(str, sizeof(data_in_file), fichier)) { // Tant qu'il y a des lignes à lire
                //printf(" \t%d \n",compteur_col);
                sscanf(str, "%lf", &nombre);
                set_matrix_value(matrice,compteur_rows,compteur_col,nombre); // On met la valeur dans la matrice
                compteur_col ++; // On change de dimenssions dans la matrice 
            }

            fclose(fichier); // On ferme le fichier
            compteur_col=0; // On remet le compteur à 0.

            compteur_rows++; // On change de fihcier dans la matrice
        }
    }

    closedir(rep); // On ferme le directorie

    return matrice;
}

/*
    Compte le nombre de fichier dans le dossier des données et compte le nombde de dimension
*/
void _count_dim_file(const char* path, int *nrows, int *ncols){

    struct dirent *de;  
    FILE *fp = NULL;
    DIR *dr = opendir(path); // On ouvre le dossier

    char path_combine [500];
    char *file_path = path;
    char str [500];
    char sentence [128];


    int c_nrows = 0;
    int c_ncols = 0;
    int premier = 0;

    while ((de = readdir(dr))) {

        c_nrows ++;

        if (premier == 0) {
            // On ouvre un fichier et on compte les dimensions
            strcpy(path_combine,file_path); // On copy le chemin du directorie
            strcpy(str,de ->d_name); // On copie le nom du fichier dans str

            strcat(path_combine,str); // On combine les deux

            FILE *fichier = fopen(path_combine,"r");

            while (fgets(str, sizeof(sentence), fichier)){
                c_ncols ++;
            }

            premier = 1;
            fclose(fichier);
        }
    }

    closedir(dr);

    *nrows = c_nrows-2;
    *ncols = c_ncols;
}

/*
    Liste les fichiers dans "data" contenus dans la dossier "path"
    Renvoi le nombre d'éléments
*/
int _list_files_in_dir(char* path, char *data[]){
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
    Ajoute au tableau les données du fichier new_point
*/
void add_new_point(char* new_point, double* new_point_num){
    FILE *fp = NULL;
    double element_value;
    int i = 0;

    if((fp = fopen(new_point, "r")) == NULL){     
        printf("Erreur du fichier %s : %s\n", new_point, strerror(errno));
    } 
    else {
        while(fscanf(fp, "%lf\n", &element_value) != EOF) {
            new_point_num[i] = element_value;
            i++;
        }
        fclose(fp);
    }
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
    Copie les données contenu dans le tableau data dans le fichier path
*/
void write_in_file(int* data,char* path, unsigned int size){

    FILE *file = NULL; // On déclare le fichier
    file = fopen(path,"w"); // On ouvre le fichier en écriture

    for (int i = 0; i < size ; i++) {
        
        fprintf(file,"Elements %d fait parti de la classe : %d \n",i+1,data[i]+1);
    }

    fclose(file);
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

    for (int i = 0; i < head->ncols; i++)
        set_matrix_value(head,nb_kluster,i,get_matrix_value(matrice,row,i));
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

        if(head[i] != tab[i]) {
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
            Le nombre de cluster
*/
void calc_centroid (unsigned int* classified,unsigned int size, Matrix* centroid, Matrix* base, unsigned int nb_cluster) {

    //On calcul le mean pour faire les centroids

    for (int cluster = 0 ; cluster < nb_cluster ; cluster ++) {// Pour chaque cluster
        
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

/*
    Renvoie le chiffre correspondant à une string donnée
    ex : str = "09" -> x = 9
*/
int get_number(char* str){
    char* res[10] = {"01", "02", "03", "04", "05", "06", "07", "08", "09"};
    
    for (int i = 0; i < 9; i++){
        if(strcmp(res[i], str) == 0)
            return i+1;
    }
    return 0;
}