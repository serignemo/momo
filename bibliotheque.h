
typedef struct {
    char titre[50];
    char auteur[50];
    int annee;
    int isbn;
    int estEmprunte;
} Livre;
typedef struct {
    int isbn;
    char nom_emprunteur[100];
    char date[11];
     char date_retour[11];
} Emprunt;
int ajouterLivre(Livre[], int);

