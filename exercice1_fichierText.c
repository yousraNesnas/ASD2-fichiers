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

/*
 * Cette fonction crée un fichier "etudiant.txt" et y enregistre les informations d'un certain nombre d'étudiants.
 */
void creer_fichier_etudiants(int n)
{
    FILE *f = fopen("etudiant.txt", "w"); // Ouvre le fichier "etudiant.txt" en mode écriture
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
        scanf("%f", &etu.moyenne);                                                      // Lit et enregistre la moyenne de l'étudiant
        fprintf(f, "%d %s %s %.2f\n", etu.matricule, etu.nom, etu.prenom, etu.moyenne); // Écrit les informations de l'étudiant dans le fichier
    }
    fclose(f); // Ferme le fichier
}

/*
 * Cette fonction affiche les informations des étudiants enregistrés dans le fichier "etudiant.txt" et calcule la moyenne du groupe.
 */
void afficher_etudiants()
{
    FILE *f = fopen("etudiant.txt", "r"); // Ouvre le fichier "etudiant.txt" en mode lecture
    Etudiant etu;                         // Déclare une variable de type Etudiant pour stocker les informations de chaque étudiant
    float moyenne_totale = 0;             // Variable pour calculer la moyenne du groupe
    int nb_etudiants = 0;                 // Variable pour compter le nombre d'étudiants
    printf("Liste des etudiants :\n");
    while (fscanf(f, "%d %s %s %f\n", &etu.matricule, etu.nom, etu.prenom, &etu.moyenne) != EOF)
    {
        // fscanf(f, "%d %s %s %f\n", &etu.matricule, etu.nom, etu.prenom, &etu.moyenne);  // Lit les informations de l'étudiant depuis le fichier
        printf("%d - %s %s - %.2f\n", etu.matricule, etu.nom, etu.prenom, etu.moyenne); // Affiche les informations de l'étudiant
        moyenne_totale += etu.moyenne;                                                  // Ajoute la moyenne de l'étudiant à la somme des moyennes
        nb_etudiants++;                                                                 // Incrémente le compteur d'étudiants
    }
    moyenne_totale /= nb_etudiants;                       // Calcule la moyenne du groupe en divisant la somme des moyennes par le nombre d'étudiants
    printf("Moyenne du groupe : %.2f\n", moyenne_totale); // Affiche la moyenne du groupe
    fclose(f);                                            // Ferme le fichier
}

/*
 * Cette fonction permet d'ajouter les informations d'un nouvel étudiant dans le fichier "etudiant.txt".
 */
void ajouter_etudiant()
{
    FILE *f = fopen("etudiant.txt", "a"); // Ouvre le fichier "etudiant.txt" en mode ajout
    Etudiant etu;                         // Déclare une variable de type Etudiant pour stocker les informations du nouvel étudiant
    printf("Saisir les informations de l'etudiant a ajouter :\n");
    printf("Matricule : ");
    scanf("%d", &etu.matricule);
    printf("Nom : ");
    scanf("%s", etu.nom);
    printf("Prenom : ");
    scanf("%s", etu.prenom);
    printf("Moyenne : ");
    scanf("%f", &etu.moyenne);
    fprintf(f, "%d %s %s %.2f\n", etu.matricule, etu.nom, etu.prenom, etu.moyenne); // Écrit les informations du nouvel étudiant dans le fichier
    fclose(f);                                                                      // Ferme le fichier
}

/*
 * Cette fonction permet d'insérer un nouvel enregistrement dans le fichier "etudiant.txt" trié par nom.
 */
void insererEtudiant()
{
    FILE *fichier = fopen("etudiant.txt", "r+"); // Ouvre le fichier "etudiant.txt" en mode lecture et écriture
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

    FILE *temp = fopen("temp.txt", "w"); // Ouvre un fichier temporaire pour stocker les enregistrements
    if (temp == NULL)
    {
        printf("Erreur lors de la creation du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    int estInserer = 0; // Variable pour vérifier si le nouvel enregistrement a été inséré
    Etudiant etud;
    while (fscanf(fichier, "%d %s %s %f\n", &etud.matricule, etud.nom, etud.prenom, &etud.moyenne) != EOF)
    {
        if (!estInserer && strcmp(e.nom, etud.nom) < 0)
        {
            fprintf(temp, "%d %s %s %.2f\n", e.matricule, e.nom, e.prenom, e.moyenne); // Écrit le nouvel enregistrement dans le fichier temporaire
            estInserer = 1;
        }
        fprintf(temp, "%d %s %s %.2f\n", etud.matricule, etud.nom, etud.prenom, etud.moyenne); // Écrit les enregistrements existants dans le fichier temporaire
    }

    if (!estInserer)
    {
        fprintf(temp, "%d %s %s %.2f\n", e.matricule, e.nom, e.prenom, e.moyenne); // Écrit le nouvel enregistrement à la fin du fichier temporaire s'il n'a pas été inséré auparavant
    }

    fclose(fichier); // Ferme le fichier d'origine
    fclose(temp);    // Ferme le fichier temporaire

    remove("etudiant.txt");             // Supprime le fichier d'origine
    rename("temp.txt", "etudiant.txt"); // Renomme le fichier temporaire en "etudiant.txt"

    printf("Etudiant insere avec succes.\n");
}

void supprimer_etudiants()
{
    FILE *fichier = fopen("etudiant.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE *tmp = fopen("tmp.txt", "w+");
    if (tmp == NULL)
    {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    Etudiant etudiant;

    // Lecture des données du fichier
    while (fscanf(fichier, "%d %s %s %f\n", &etudiant.matricule, etudiant.nom, etudiant.prenom, &etudiant.moyenne) != EOF)
    { // Si la moyenne de l'étudiant est supérieure ou égale à 10, le copier dans le fichier temporaire
        if (etudiant.moyenne >= 10)
        {
            fprintf(tmp, "%d %s %s %.2f\n", etudiant.matricule, etudiant.nom, etudiant.prenom, etudiant.moyenne);
        }
    }
    fclose(fichier);
    fclose(tmp);
    // Supprimer le fichier original
    remove("etudiant.txt");
    // Renommer le fichier temporaire avec le nom original
    rename("tmp.txt", "etudiant.txt");
    printf("Les etudiants avec une moyenne inferieure a 10 ont ete supprimes avec succes.\n");

    // Réouvrir le fichier en mode lecture
    fichier = fopen("etudiant.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier etudiant.txt.\n");
        return;
    }

    // Lire et afficher les étudiants restants dans le fichier
    printf("Etudiants restants :\n");
    while (fscanf(fichier, "%d %s %s %f\n", &etudiant.matricule, etudiant.nom, etudiant.prenom, &etudiant.moyenne) != EOF)
    {
        printf("Matricule : %d, Nom : %s, Prenom : %s, Moyenne : %.2f\n",
               etudiant.matricule, etudiant.nom, etudiant.prenom, etudiant.moyenne);
    }

    fclose(fichier);
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
    ajouter_etudiant(); // Appelle la fonction pour ajouter un nouvel étudiant au fichier
    printf("\n****************************************************\n");
    insererEtudiant(); // Appelle la fonction pour insérer un nouvel étudiant dans le fichier trié par ordre alphabétique
    printf("\n****************************************************\n");
    supprimer_etudiants(); // Appelle la fonction pour supprimer des étudiants du fichier
}
