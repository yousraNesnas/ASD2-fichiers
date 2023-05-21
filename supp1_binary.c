#include <stdio.h>

void enregistrer_valeurs(FILE *fichier) {
    int valeur;
    printf("Entrez les valeurs entières positives (terminer avec une valeur négative) :\n");

    while (1) {
        scanf("%d", &valeur);

        if (valeur < 0) {
            break;  // Sortir de la boucle si une valeur négative est saisie
        }

        fwrite(&valeur, sizeof(int), 1, fichier);  // Écrire la valeur dans le fichier binaire
    }

    printf("Enregistrement des valeurs terminé.\n");
}

void retrouver_valeur(FILE *fichier, int rang) {
    int valeur;
    int trouve = 0;

    // Positionner le curseur du fichier à la position du rang demandé
    fseek(fichier, (rang - 1) * sizeof(int), SEEK_SET);

    // Lire la valeur à cette position
    if (fread(&valeur, sizeof(int), 1, fichier) == 1) {
        printf("Valeur trouvée : %d\n", valeur);
        trouve = 1;
    }

    if (!trouve) {
        printf("Le rang demandé dépasse la taille du fichier.\n");
    }
}

int main() {
    FILE *fichier = fopen("valeurs.bin", "wb+");
    int rang;

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    enregistrer_valeurs(fichier);

    printf("Entrez le rang de la valeur à retrouver : ");
    scanf("%d", &rang);

    // Retourner au début du fichier
    fseek(fichier, 0, SEEK_SET);

    retrouver_valeur(fichier, rang);

    fclose(fichier);

    return 0;
}
