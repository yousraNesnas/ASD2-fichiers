#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nom[20], prenom[20], poste[50], date_rec[10];
} Employe;

typedef struct
{
    char poste[50];
    long salaire;
} Poste;

void stockerListeEmployes(Employe T[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Saisir les information de l'employe n° %d : \n", i + 1);
        printf("Nom : ");
        scanf("%s", T[i].nom);
        printf("Prenom : ");
        scanf("%s", T[i].prenom);
        printf("Poste : ");
        scanf("%s", T[i].poste);
        printf("Date de recrutement : ");
        scanf("%s", T[i].date_rec);
    }
}

void stockerListePoste(Poste T[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Saisir les information du poste n° %d : \n", i + 1);
        printf("Poste : ");
        scanf("%s", T[i].poste);
        printf("Salaire : ");
        scanf("%ld", T[i].salaire);
    }
}

void salaire(Poste T_postes[], Employe T_emp[], int m, int n)
{
    char nom[20], prenom[20];
    int x;
    do
    {
        printf("Donnez le nom et le prenom d'un employé :\n");
        printf("Nom:");
        scanf("%s", nom);
        printf("Prenom:");
        scanf("%s", prenom);

        for (int i = 0; i < n; i++)
        {
            if (strcmp(T_emp[i].nom, nom) == 0 && strcmp(T_emp[i].prenom, prenom) == 0)
            {
                for (int j = 0; j < m; j++)
                {
                    if (strcmp(T_emp[i].poste, T_postes[j].poste) == 0)
                    {
                        printf("Le salaire de %s %s pour le poste %s est %ld DA\n", nom, prenom, T_emp[i].poste, T_postes[j].salaire);
                        return;
                    }
                }
            }
        }
        printf("Voulez vous refaire pour un autre employé? 1 => oui / 0 => non\n");
    } while (x == 1);
}

int main()
{
    int nbr_poste, nbr_emp, x = 0;
    Poste T_postes[100];
    Employe T_emp[100];
    char nom[20], prenom[20];
    printf("\t \t \t Automatisation de la gestion de carriere\n");
    printf("Donnez le nombre de postes que vous voulez stocker SVP : ");
    scanf("%d", &nbr_poste);
    stockerListePoste(T_postes, nbr_poste);
    printf("Donnez le nombre d'employés que vous voulez stocker SVP : ");
    scanf("%d", &nbr_emp);
    stockerListePoste(T_emp, nbr_emp);
    printf("Determiner salsire\n");
    salaire(T_postes, T_emp, nbr_poste, nbr_emp);
}