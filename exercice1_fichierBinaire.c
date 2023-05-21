#include <stdio.h>  // Bibliothèque standard pour les entrées/sorties
#include <stdlib.h> // Bibliothèque standard pour les fonctions de base (allocation mémoire, conversion de types, etc.)
#include <string.h> // Bibliothèque standard pour les fonctions de manipulation de chaînes de caractères

#define MAX_NOM 50        // Définition d'une constante MAX_NOM avec la valeur 50, représentant la longueur maximale d'un nom d'étudiant
#define MAX_ETUDIANTS 100 // Définition d'une constante MAX_ETUDIANTS avec la valeur 100, représentant le nombre maximal d'étudiants
#define MAX_PRENOM 20     // Définition d'une constante MAX_PRENOM avec la valeur 20, représentant la longueur maximale d'un prénom d'étudiant

typedef struct
{
    int matricule;
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    float moyenne;
} Etudiant;

void creer_fichier_etudiants(int n)
{
    FILE *f = fopen("etudiant1.txt", "wb"); // Ouvre le fichier "etudiant.txt" en mode écriture binaire

    for (int i = 0; i < n; i++)
    {
        Etudiant etu; // Déclare une variable de type Etudiant pour stocker les informations de l'étudiant

        printf("Saisir les informations de l'etudiant %d :\n", i + 1);
        printf("Matricule : ");
        scanf("%d", &etu.matricule); // Lit et enregistre le matricule de l'étudiant

        printf("Nom : ");
        scanf("%s", etu.nom); // Lit et enregistre le nom de l'étudiant

        printf("Prenom : ");
        scanf("%s", etu.prenom); // Lit et enregistre le prénom de l'étudiant

        printf("Moyenne : ");
        scanf("%f", &etu.moyenne); // Lit et enregistre la moyenne de l'étudiant

        fwrite(&etu, sizeof(Etudiant), 1, f); // Écrit les informations de l'étudiant dans le fichier binaire
    }

    fclose(f); // Ferme le fichier
}
void afficher_etudiants()
{
    FILE *f = fopen("etudiant1.txt", "rb"); // Ouvre le fichier "etudiant.txt" en mode lecture binaire

    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Etudiant etu;
    float moyenne_totale = 0;
    int nb_etudiants = 0;

    printf("Liste des etudiants :\n");

    while (fread(&etu, sizeof(etu), 1, f) == 1) // Lit les enregistrements étudiants à partir du fichier
    {
        printf("%d - %s %s - %.2f\n", etu.matricule, etu.nom, etu.prenom, etu.moyenne);
        moyenne_totale += etu.moyenne;
        nb_etudiants++;
    }

    moyenne_totale /= nb_etudiants;
    printf("Moyenne du groupe : %.2f\n", moyenne_totale);

    fclose(f); // Ferme le fichier
}
void insererEtudiant()
{
    FILE *fichier = fopen("etudiant1.txt", "r+b"); // Ouvre le fichier "etudiant.txt" en mode lecture et écriture binaire
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Etudiant e; // Déclare une variable de type Etudiant pour stocker les informations du nouvel étudiant
    printf("Entrez le numero de matricule: ");
    scanf("%d", &e.matricule);
    printf("Entrez le nom: ");
    scanf("%s", e.nom);
    printf("Entrez le prenom: ");
    scanf("%s", e.prenom);
    printf("Entrez la moyenne: ");
    scanf("%f", &e.moyenne);

    FILE *temp = fopen("temp.txt", "wb"); // Ouvre un fichier temporaire en mode écriture binaire pour stocker les enregistrements
    if (temp == NULL)
    {
        printf("Erreur lors de la creation du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    int estInserer = 0; // Variable pour vérifier si le nouvel enregistrement a été inséré
    Etudiant etud;
    while (fread(&etud, sizeof(Etudiant), 1, fichier) == 1) // Lit les enregistrements étudiants à partir du fichier
    {
        if (!estInserer && strcmp(e.nom, etud.nom) < 0)
        {
            fwrite(&e, sizeof(Etudiant), 1, temp); // Écrit le nouvel enregistrement dans le fichier temporaire
            estInserer = 1;
        }
        fwrite(&etud, sizeof(Etudiant), 1, temp); // Écrit les enregistrements existants dans le fichier temporaire
    }

    if (!estInserer)
    {
        fwrite(&e, sizeof(Etudiant), 1, temp); // Écrit le nouvel enregistrement à la fin du fichier temporaire s'il n'a pas été inséré auparavant
    }

    fclose(fichier);    // Ferme le fichier d'origine
    fclose(temp);       // Ferme le fichier temporaire

    remove("etudiant1.txt");             // Supprime le fichier d'origine
    rename("temp.txt", "etudiant1.txt"); // Renomme le fichier temporaire en "etudiant.txt"

    printf("Etudiant insere avec succes.\n");
}

void inserer_etudiant_tri()
{
    FILE *f = fopen("etudiant1.txt", "r+");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    Etudiant temp;
    Etudiant e; // Déclare une variable de type Etudiant pour stocker les informations du nouvel étudiant
    printf("Entrez le numero de matricule: ");
    scanf("%d", &e.matricule);
    printf("Entrez le nom: ");
    scanf("%s", e.nom);
    printf("Entrez le prenom: ");
    scanf("%s", e.prenom);
    printf("Entrez la moyenne: ");
    scanf("%f", &e.moyenne);
    long position = 0;
    // Boucle de lecture des enregistrements dans le fichier
    while (fread(&temp, sizeof(temp), 1, f) == 1)
    {
        // Si le nom de l'étudiant à insérer est inférieur au nom de l'étudiant lu
        if (strcmp(e.nom, temp.nom) < 0)
        { // On se replace à la position de l'enregistrement lu précédemment
            // SEEK_SET : on se positionne par rapport au début du fichier ;
            fseek(f, position, SEEK_SET);
            // On insère l'étudiant à la position courante
            fwrite(&e, sizeof(e), 1, f);

            // On réécrit l'enregistrement lu précédemment juste après l'étudiant inséré
            fwrite(&temp, sizeof(temp), 1, f);

            fclose(f);
            return;
        }
        // On met à jour la position pour la prochaine itération
        position = ftell(f);
    }
    // Si on arrive ici, cela veut dire que l'étudiant à insérer est le dernier de la liste
    // On l'insère donc en fin de fichier
    fwrite(&e, sizeof(e), 1, f);
    fclose(f);
}

int main()
{
    int n;
    printf("Donnez le nombre d'etudiants que vous voullez enregistrer :");
    scanf("%d", &n);
    creer_fichier_etudiants(n); // Appelle la fonction pour créer le fichier et enregistrer les étudiants
    printf("\n****************************************************\n");
    afficher_etudiants(); // Appelle la fonction pour afficher les étudiants du fichier
    printf("\n****************************************************\n");
    // ajouter_etudiant(); // Appelle la fonction pour ajouter un nouvel étudiant au fichier
    printf("\n****************************************************\n");
    insererEtudiant(); // Appelle la fonction pour insérer un nouvel étudiant dans le fichier trié par ordre alphabétique
    afficher_etudiants(); // Appelle la fonction pour afficher les étudiants du fichier
    printf("\n****************************************************\n");
    inserer_etudiant_tri();
    afficher_etudiants();
    printf("\n****************************************************\n");
    // supprimer_etudiants(); // Appelle la fonction pour supprimer des étudiants du fichier
}
