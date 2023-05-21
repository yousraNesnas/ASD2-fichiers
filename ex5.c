#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nom;
    int coordX;
    int coordY;
} Point;

void creer_fichier_points()
{
    char nomFichier[100];
    printf("Nom du fichier à créer : ");
    scanf("%s", nomFichier);

    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }

    Point point;
    printf("Donner le nom (* pour finir) et les coordonnées des points :\n");
    while (1)
    {
        printf("Nom : ");
        scanf(" %c", &point.nom);

        if (point.nom == '*')
        {
            break;
        }

        printf("Coordonnée X : ");
        scanf("%d", &point.coordX);

        printf("Coordonnée Y : ");
        scanf("%d", &point.coordY);

        fprintf(fichier, "%c %d %d\n", point.nom, point.coordX, point.coordY);
    }

    fclose(fichier);
    printf("Le fichier a été créé avec succès.\n");
}
void lister_contenu_fichier_points(const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Point point;
    printf("Contenu du fichier %s :\n", nomFichier);
    while (fscanf(fichier, " %c %d %d\n", &point.nom, &point.coordX, &point.coordY) != EOF)
    {
        printf("Nom: %c, Coordonnées: (%d, %d)\n", point.nom, point.coordX, point.coordY);
    }

    fclose(fichier);
}

void rechercher_point(const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Point point;
    int numPoints = 0;

    // Compter le nombre de points dans le fichier
    while (fscanf(fichier, " %c %d %d\n", &point.nom, &point.coordX, &point.coordY) != EOF)
    {
        numPoints++;
    }

    if (numPoints == 0)
    {
        printf("Le fichier est vide.\n");
        fclose(fichier);
        return;
    }

    printf("Votre fichier comporte %d point(s)\n", numPoints);

    int numero;
    while (1)
    {
        printf("Numéro du point cherché (0 pour finir) ? : ");
        scanf("%d", &numero);

        if (numero == 0)
        {
            printf("A bientôt !\n");
            break;
        }

        if (numero < 1 || numero > numPoints)
        {
            printf("Numéro incorrect\n");
            continue;
        }

        // Réinitialiser le pointeur du fichier
        fseek(fichier, 0, SEEK_SET);

        int i = 1;
        while (fscanf(fichier, " %c %d %d\n", &point.nom, &point.coordX, &point.coordY) != EOF)
        {
            if (i == numero)
            {
                printf("Point numéro %d est : %c %d %d\n", numero, point.nom, point.coordX, point.coordY);
                break;
            }
            i++;
        }
    }

    fclose(fichier);
}

int main()
{
    creer_fichier_points();
    const char *nomFichier = "courbe.txt";
    lister_contenu_fichier_points(nomFichier);
    rechercher_point(nomFichier);
    return 0;
}
