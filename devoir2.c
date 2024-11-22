#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *optarg ;
extern int optind, opterr, optopt;

void write_matrix_text(char *filename, int **mat, int size) {
    FILE *file = fopen(filename,"a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return ;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(file, "%d", mat[i][j]);
        fprintf(file,"\n");
    }
    fclose(file);
    printf("Matrice enregistré au format texte dans le fichier : %s\n", filename);
}

void write_matrix_binary(const char *filename, int **mat, int size) {
   /* FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return ;
    }
    for (int i = 0; i < size; i++){
        fwrite(mat[i], sizeof(int), size, file);
        printf("\n");
    }
    fclose(file);
   printf("Vecteur enregistré au format binaire dans le fichier : %s\n", filename);*/
}

void read_matrix_text(char *filename, int **mat, int size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return ;
    }

    mat = malloc(size*sizeof(int*));
    if (mat == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        return ;
    }
    for (int i = 0; i < size; i++){
        mat[i] = malloc(size*sizeof(int));
        if (mat[i] == NULL) {
            perror("Erreur d'allocation mémoire");
            fclose(file);
            return ;
        }
        for (int j = 0; j < size; j++){
            fscanf(file,"%d",mat[i][j]);
        }
    }
    fclose(file);
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++)
             printf("%d \t", mat[i][j]);
        printf("\n");

    for (int i = 0; i < size; i++) 
        free(mat[i]);
    free(mat);
}

void read_matrix_binary(const char *filename) {
   /* FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int value;
    printf("Contenu du fichier (format binaire) :\n");
    while (fread(&value, sizeof(int), 1, file) == 1) {
       printf("%d ", value);
    }
    printf("\n");
    fclose(file);*/
}

void creation_matrice_aleatoire(int **mat , int taille){
    for(int i=0 ; i<taille ;i++)
        for(int j=0 ; j<taille ; j++)
            mat[i][j] = rand()%100 ; //Remplir la matrice avec des valeurs comprises entre 0 et 99
        printf("création avec succes \n");
}



int main(int argc, char *argv[]) {
     if( argc < 6){
        printf("Nombre arguments insuffisant sur la ligne de commande .\n");
        printf("Usage : nomfichier <arg2> <arg3> <arg4> <arg5> <arg6>  .\n ",argv[0]);
        return 0 ;
    }
    int **mat ;
    int taille; //La taille de la matrice::
    char *filename ; //nomDuFichier::

    int opt  ;
    int format = 0 ; //mode binaire = 1 mode texte = 0

    while ((opt = getopt(argc, argv, "abcd:f:t")) != -1) {
        switch (opt) {
        case 'd':
            //Specifie la dimension de la matrice::
            taille = atoi(optarg);
            break;  
        
        case 'b':
            //Indique que c'est en mode binaire:
            format = 1 ;
            break;    
        case 't':
            //Indique que le format du fichier est en mode texte::
            format = 0 ;
            break ;
        
        case 'f':
            //Specifie le nom du fichier::
            filename = optarg ;
            break ;
        case 'c':
             //Permet la creation d'une matrice aleatoire::
             creation_matrice_aleatoire(mat,taille);
             if(format == 1){
                //write_matrix_binary(filename,mat,taille);
                printf("pas encore pret\n");
            }
            else{
                write_matrix_text(filename,mat,taille);
            }
            break;
        case 'a':
            //Indiquer au programme d'afficher le contenu du fichier::
            if(format)
                //read_matrix_binary(filename);
                printf("pas encore pret\n");
            else
                read_matrix_text(filename,mat,taille);
            break;
        case ':' :
            printf("Option necessite un argument\n");break;
        case '?' :
            printf("Aucune action effectuée\n");break;
        }
    }
    for (; optind < argc; optind++)
    {
        printf("argument : %s\n",argv[optind] );
    }
    if (filename == NULL && mat == NULL) {
       fprintf(stderr, "Aucune action effectuée. Utilisez -w, -r, -c ou -v.\n");
        return 1;
    }

    return 0;
}
