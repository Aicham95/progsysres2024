#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

// Fonction pour créer une matrice aléatoire
void create_random_matrix(int dimension, int matrix[dimension][dimension]) {
    srand(time(NULL));
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] = rand() % 100; // Nombres aléatoires entre 0 et 99
        }
    }
}

// Fonction pour écrire une matrice au format texte
void write_matrix_to_text(const char *filename, int dimension, int matrix[dimension][dimension]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fonction pour écrire une matrice au format binaire
void write_matrix_to_binary(const char *filename, int dimension, int matrix[dimension][dimension]) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
        exit(EXIT_FAILURE);
    }

    fwrite(&dimension, sizeof(int), 1, file);
    for (int i = 0; i < dimension; i++) {
        fwrite(matrix[i], sizeof(int), dimension, file);
    }

    fclose(file);
}

// Fonction pour lire une matrice depuis un fichier texte
void read_matrix_from_text(const char *filename, int dimension, int matrix[dimension][dimension]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour lecture");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
}

// Fonction pour lire une matrice depuis un fichier binaire
void read_matrix_from_binary(const char *filename, int dimension, int matrix[dimension][dimension]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier pour lecture");
        exit(EXIT_FAILURE);
    }

    int file_dimension;
    fread(&file_dimension, sizeof(int), 1, file);
    if (file_dimension != dimension) {
        fprintf(stderr, "Dimension de la matrice dans le fichier (%d) ne correspond pas à celle spécifiée (%d).\n", file_dimension, dimension);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimension; i++) {
        fread(matrix[i], sizeof(int), dimension, file);
    }

    fclose(file);
}

// Fonction pour afficher une matrice
void display_matrix(int dimension, int matrix[dimension][dimension]) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int dimension = 0;
    char *filename = NULL;
    int create = 0, display = 0, binary = 1, text = 0;

    int opt;
    while ((opt = getopt(argc, argv, "cad:bf:t")) != -1) {
        switch (opt) {
            case 'c': create = 1; break;
            case 'a': display = 1; break;
            case 'd': dimension = atoi(optarg); break;
            case 'b': binary = 1; text = 0; break;
            case 't': text = 1; binary = 0; break;
            case 'f': filename = optarg; break;
            default:
                fprintf(stderr, "Usage: %s [-c | -a] -d dimension -f filename [-b | -t]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (dimension <= 0 || filename == NULL) {
        fprintf(stderr, "Dimension et nom du fichier sont obligatoires.\n");
        exit(EXIT_FAILURE);
    }

    int matrix[dimension][dimension];

    if (create) {
        // Création d'une matrice aléatoire
        create_random_matrix(dimension, matrix);
        if (binary) {
            write_matrix_to_binary(filename, dimension, matrix);
        } else {
            write_matrix_to_text(filename, dimension, matrix);
        }
        printf("Matrice créée et enregistrée dans le fichier '%s'.\n", filename);
    }

    if (display) {
        if (binary) {
            read_matrix_from_binary(filename, dimension, matrix);
        } else {
            read_matrix_from_text(filename, dimension, matrix);
        }
        printf("Matrice lue depuis le fichier '%s' :\n", filename);
        display_matrix(dimension, matrix);
    }
    return 0;
}
