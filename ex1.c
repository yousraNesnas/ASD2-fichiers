#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int Nm;
    char nom[20];
    char prenom[20];
    float moy;
} Etudiant;
void creefichier(int n)
{
    FILE *f;
    f = fopen("ETUDIANT.txt", "w");
    Etudiant e;
    for (int i = 0; i < n; i++)
    {
        printf("Saisir les informations de l'etudiant %d :\n", i + 1);
        printf("Matricule : ");
        scanf("%d", &e.Nm); // Lit et enregistre le matricule de l'étudiant
        printf("Nom : ");
        scanf("%s", e.nom); // Lit et enregistre le nom de l'étudiant
        printf("Prenom : ");
        scanf("%s", e.prenom); // Lit et enregistre le prénom de l'étudiant
        printf("Moyenne : ");
        scanf("%f", &e.moy);                                         // Lit et enregistre la moyenne de l'étudiant
        fprintf(f, "%d %s %s %.2f\n", e.Nm, e.nom, e.prenom, e.moy); // Écrit les informations de l'étudiant dans le fichier
    }
    fclose(f);
}
void inserer();

int main()
{
    int n;
    printf("donner le nmbre de etudiant: ");
    scanf("%d", &n);
    creefichier(n);
    inserer();
}

void inserer()
{
    FILE *f;
    f = fopen("etudiant.txt", "r");

    FILE *fp;
    fp = fopen("etudiant2.txt", "a");
    Etudiant e, e1;
    while (fscanf(f, " %d  %s  %s  %f ", &e.Nm, e.nom, e.prenom, &e.moy) != EOF)
    {
        fprintf(fp, " %d  %s  %s  %f ", e.Nm, e.nom, e.prenom, e.moy);
        /* code */
    }

     printf("Saisir les informations de l'etudiant:\n");
        printf("Matricule : ");
        scanf("%d", &e1.Nm); // Lit et enregistre le matricule de l'étudiant
        printf("Nom : ");
        scanf("%s", e1.nom); // Lit et enregistre le nom de l'étudiant
        printf("Prenom : ");
        scanf("%s", e1.prenom); // Lit et enregistre le prénom de l'étudiant
        printf("Moyenne : ");
        scanf("%f", &e1.moy);                                         // Lit et enregistre la moyenne de l'étudiant
        fprintf(fp, "%d %s %s %.2f\n", e1.Nm, e1.nom, e1.prenom, e1.moy); 
        
   fclose(f);
   fclose(fp);
}
