
#include <stdio.h>
#include "bibliotheque.h"
#include<string.h>
#define MAX 100
int generer_isbn()
{
    static int isbn_courant = 10000; //memoriser l'état entre les appels
    isbn_courant++;
    return isbn_courant;
}
int ajouterLivre(Livre livres[], int nb)
{
    if (nb > MAX)
        return 0;
    printf("Titre du livre : ");
    gets(livres[nb].titre);
    printf("Auteur du livre : ");
    gets(livres[nb].auteur);
    printf("Annee : ");
    scanf("%d",&livres[nb].annee);
    livres[nb].isbn = generer_isbn();
    getchar();
    livres[nb].estEmprunte = 0;
    return 1;
}

void afficherLivre(Livre livres[], int nb)
{
    if (nb == 0)
    {
        printf("Aucun livre enregistre pour le moment.\n");
        return;
    }

    printf("\nListe des livres enregistres :\n\n");
    printf("Y'a %d Enregistre !!!",nb);
    for (int i = 0; i < nb; i++)
    {
        printf("\nLivre %d\n", i + 1);
        printf("Titre  : %s\n", livres[i].titre);
        printf("Auteur : %s\n", livres[i].auteur);
        printf("Annee  : %d\n",livres[i].annee);
        printf("ISBN   : %d\n", livres[i].isbn);
        if (livres[i].estEmprunte == 1)
        {
            printf("Etat   : Emprunte\n");
        }
        else
        {
            printf("Etat   : Disponible\n");
        }
    }
}
void rechercherLivre(Livre livres[], int nb)
{
    char recherche[50];
    int trouve = 0;

    if (nb == 0)
    {
        printf("Aucun livre enregistre.\n");
        return;
    }

    printf("Titre du livre a rechercher : ");
    gets(recherche);

    for (int i = 0; i < nb; i++)
    {
        if (strcasecmp(livres[i].titre, recherche) == 0)
        {
            printf("\nLivre trouve :\n");
            printf("Titre  : %s\n", livres[i].titre);
            printf("Auteur : %s\n", livres[i].auteur);
            printf("Annee  : %d\n", livres[i].annee);
            printf("ISBN   : %d\n", livres[i].isbn);
            if (livres[i].estEmprunte == 1)
            {
                printf("Etat   : Emprunte\n");
            }
            else
            {
                printf("Etat   : Disponible\n");
            }
            trouve = 1;
            break;
        }
    }

    if (!trouve)
    {
        printf("Aucun livre ne correspond a ce titre.\n");
    }
}
int supprimerLivre(Livre livres[], int nb)
{
    int isbn;
    printf("ISBN du livre a supprimer : ");
    scanf("%d", &isbn);

    for (int i = 0; i < nb; i++) {
        if (livres[i].isbn == isbn) {
            livres[i] = livres[nb-1];
            nb--;
            printf("Livre supprime avec succes.\n");
            return nb;
        }
    }
    printf("Livre non trouve.\n");
    return nb;
}
void emprunterLivre(Livre livres[], Emprunt emprunts[], int nb, int nbEmprunts)
{
    int isbn;
    if (nb == 0)
    {
        printf("Aucun livre n'est disponible dans la bibliotheque.\n");
        return 0;
    }
    printf("Entrez l'ISBN du livre a emprunter : ");
    scanf("%d", &isbn);
    getchar();
    int trouve = 0;
    for (int i = 0; i < nb; i++)
    {
        if (livres[i].isbn == isbn && livres[i].estEmprunte == 0)
        {
            livres[i].estEmprunte = 1;
            emprunts[nbEmprunts].isbn = isbn;
            printf("Nom de l'etudiant emprunteur : ");
            gets(emprunts[nbEmprunts].nom_emprunteur);
            printf("Date d'emprunt (jj/mm/aaaa) : ");
            gets(emprunts[nbEmprunts].date);
            printf("Date de retour prevue (jj/mm/aaaa) : ");
            gets(emprunts[nbEmprunts].date_retour);
            nbEmprunts++;
            trouve = 1;
            printf("Livre emprunte avec succes.\n");
            break;
        }
    }
    if (trouve == 0)
    {
        printf("Livre non disponible ou ISBN incorrect ou deja emprunter.\n");
    }
}

void afficherEmprunts(Emprunt emprunts[], int nbEmprunts)
{
    if (nbEmprunts == 0)
    {
        printf("Aucun emprunt enregistre.\n");
    }
    else
    {
        printf("\nListe des emprunts en cours :\n");
        for (int i = 0; i < nbEmprunts; i++)
        {
            printf("Emprunt %d :\n", i + 1);
            printf("ISBN             : %d\n", emprunts[i].isbn);
            printf("Emprunteur       : %s\n", emprunts[i].nom_emprunteur);
            printf("Date d'emprunt   : %s\n", emprunts[i].date);
            printf("Date de retour   : %s\n\n", emprunts[i].date_retour);
        }
    }
}

void retournerLivre(Livre livres[], int nb)
{
    int isbn;
    int jours_retard;
    printf("Saisir l'ISBN du livre a retourner : ");
    scanf("%d", &isbn);
    int trouve = 0;
    for (int i = 0; i < nb; i++)
    {
        if (livres[i].isbn == isbn)
        {
            trouve = 1;
            if (livres[i].estEmprunte == 1)
            {
                livres[i].estEmprunte = 0;
                printf("Combien de jours de retard ? ");
                scanf("%d", &jours_retard);
                if (jours_retard > 0)
                {
                    int amende = jours_retard * 500;
                    printf("Vous devez payer une amende de %d pour %d jour(s) de retard.\n", amende, jours_retard);

                }
                else
                {
                    printf("Retour fait dans les temps. Aucune amende.\n");
                }

                printf("Livre retourner avec succes !\n");
            }
            else
            {
                printf("Ce livre n'etait pas emprunte.\n");
            }
        }
    }

    if (!trouve)
    {
        printf("Livre non trouve.\n");
    }
}

void statistiques(Livre livres[], int nb)
{
    int nbEmpruntes = 0;
    int nbDisponibles = 0;
    for (int i = 0; i < nb; i++)
    {
        if (livres[i].estEmprunte == 1)
            nbEmpruntes++;
        else
            nbDisponibles++;
    }
    printf("\nStatistiques de la bibliotheque :\n");
    printf("Nombre total de livres        : %d\n", nb);
    printf("Nombre de livres empruntes    : %d\n", nbEmpruntes);
    printf("Nombre de livres disponibles  : %d\n", nbDisponibles);
}
void menu()
{
    printf("\033[1;36m**************** BIENVENUE DANS LE GESTIONNAIRE DE BIBLIOTHEQUE ********************\033[0m\n");
    printf("1. Ajouter un livre\n");
    printf("2. Afficher les livres\n");
    printf("3. Rechercher un livre par son titre\n");
    printf("4. Supression d'un livre par son ISBN\n");
    printf("5. Emprunt d'un livre par son ISBN\n");
    printf("6. Retourner le livre  emprunter par son ISBN\n");
    printf("7. Afficher les emprunts en cours\n");
    printf("8. Affichage des statistiques du bibliotheque\n");
    printf("0. Quitter\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
void principal()
{
    Livre livres[MAX];
    int nb = 0, choix;
    Emprunt emprunts[MAX];
    int nbEmprunts = 0, nonEmprunt = 0;
    while(1)
    {
        system("pause");
        system("cls");
        menu();
        printf("Saisir votre choix: ");
        scanf(" %d", &choix);
        getchar(); // absorbe le \n après le choix
        switch(choix)
        {
        case 1:
            if (ajouterLivre(livres, nb) == 1)
            {
                nb++;
                printf("Le livre a ete ajoute avec succes !\n");
            }
            else
            {
                printf("La bibliotheque est pleine.\n");
            }
            break;
        case 2:
            afficherLivre(livres, nb);
            break;
        case 3:
            rechercherLivre(livres, nb);
            break;
        case 4:
           nb=supprimerLivre(livres, nb);
            break;
        case 5:
            emprunterLivre(livres, emprunts, nb, nbEmprunts);
            nbEmprunts++;
            break;
        case 6:
            retournerLivre(livres, nb);
            break;
        case 7:
            afficherEmprunts(emprunts, nbEmprunts);
            break;
        case 8:
            statistiques(livres, nb);
            break;
        case 0:
            printf("Au revoir !\n");
            return;

        default:
            printf("Choix invalide , veuillez reessayer.\n");
        }
    }
}

