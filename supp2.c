#include <stdio.h>
#include <stdlib.h>
void triCroissant(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    FILE *fichier = fopen("entiers.txt", "r");
    int tableau[10];

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lecture des 10 entiers à partir du fichier

    // for (int i = 0; i < 10; i++)
    // {
    //     scanf("%d", &tableau[i]);
    //     fprintf(fichier, "%d", tableau[i]);
    // }

    for (int i = 0; i < 10; i++)
    {
        fscanf(fichier, "%d", &tableau[i]);
    }

    // Tri du tableau dans l'ordre croissant
    triCroissant(tableau, 10);
    fclose(fichier);
    // Retour au début du fichier
    // fseek(fichier, 0, SEEK_SET);
    fichier = fopen("entiers.txt", "w");
    // Enregistrement du tableau trié dans le fichier
    for (int i = 0; i < 10; i++)
    {
        fprintf(fichier, "%d ", tableau[i]);
    }

    fclose(fichier);

    printf("Le tableau trié a été enregistré dans le fichier avec succès.\n");
}
