#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fonction pour découper un fichier en plusieurs parties
void split_file(const char *filename, size_t part_size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Déterminer la taille du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Calculer le nombre de parties
    int part_count = (file_size + part_size - 1) / part_size;

    // Créer et écrire les parties
    char part_filename[256];
    for (int i = 0; i < part_count; i++) {
        snprintf(part_filename, sizeof(part_filename), "%s.part%d", filename, i + 1);
        FILE *part_file = fopen(part_filename, "wb");
        if (part_file == NULL) {
            perror("Erreur lors de l'ouverture d'une partie");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        char *buffer = malloc(part_size);
        if (buffer == NULL) {
            perror("Erreur d'allocation mémoire");
            fclose(part_file);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        size_t bytes_read = fread(buffer, 1, part_size, file);
        fwrite(buffer, 1, bytes_read, part_file);

        free(buffer);
        fclose(part_file);
    }

    fclose(file);
    printf("Fichier '%s' découpé en %d parties de taille %zu octets.\n", filename, part_count, part_size);
}

// Fonction pour rassembler les parties d'un fichier
void join_files(const char *output_filename, int part_count, char *part_filenames[]) {
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    // Lire et écrire chaque partie
    for (int i = 0; i < part_count; i++) {
        FILE *part_file = fopen(part_filenames[i], "rb");
        if (part_file == NULL) {
            perror("Erreur lors de l'ouverture d'une partie");
            fclose(output_file);
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), part_file)) > 0) {
            fwrite(buffer, 1, bytes_read, output_file);
        }

        fclose(part_file);
    }

    fclose(output_file);
    printf("Fichier reconstitué et sauvegardé sous '%s'.\n", output_filename);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage :\n");
        fprintf(stderr, "  Découper un fichier : %s split nomfichier taille\n", argv[0]);
        fprintf(stderr, "  Rassembler des parties : %s join fichier_sortie part1 part2 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "split") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage : %s split nomfichier taille\n", argv[0]);
            return EXIT_FAILURE;
        }

        const char *filename = argv[2];
        size_t part_size = strtoul(argv[3], NULL, 10);
        if (part_size <= 0) {
            fprintf(stderr, "Taille invalide : %s\n", argv[3]);
            return EXIT_FAILURE;
        }

        split_file(filename, part_size);
    } else if (strcmp(argv[1], "join") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage : %s join fichier_sortie part1 part2 ...\n", argv[0]);
            return EXIT_FAILURE;
        }

        const char *output_filename = argv[2];
        int part_count = argc - 3;
        char **part_filenames = &argv[3];

        join_files(output_filename, part_count, part_filenames);
    } else {
        fprintf(stderr, "Commande invalide : %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
