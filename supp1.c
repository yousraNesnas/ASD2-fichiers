#include <stdio.h>

void enregistrer_valeurs(FILE *fichier) {
    int valeur;
    printf("Entrez les valeurs entières positives (terminer avec une valeur négative) :\n");
    
    while (1) {
        scanf("%d", &valeur);
        
        if (valeur < 0) {
            break;  // Sortir de la boucle si une valeur négative est saisie
        }
        
        fprintf(fichier, "%d\n", valeur);  // Écrire la valeur dans le fichier
    }
    
    printf("Enregistrement des valeurs terminé.\n");
}

void retrouver_valeur(FILE *fichier, int rang) {//4
    int valeur;
    int i = 1;
    int trouve = 0;
    
    // Rechercher la valeur de rang demandé dans le fichier
    while (fscanf(fichier, "%d", &valeur) != EOF) {
        if (i == rang) {
            printf("Valeur trouvée : %d\n", valeur);
            trouve = 1;
            break;
        }
        i++;
    }
    
    if (!trouve) {
        printf("Le rang demandé dépasse la taille du fichier.\n");
    }
}

int main() {
    FILE *fichier = fopen("valeurs.txt", "w+");
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
