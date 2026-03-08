#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"

Arbre lire_arbre(FILE* fichier) {
    int val;
    int val_lu = fscanf(fichier, " %d", &val);

    if (!val_lu) {
        return NULL;
    }

    // Si le noeud est vide, on renvoie un pointeur NULL
    if (val == 0) {
        return NULL;
    }
    // Sinon on crée une cellule
    Arbre noeud = alloue_noeud(val);
    if (noeud != NULL) { 
        noeud->fg = lire_arbre(fichier);
        noeud->fd = lire_arbre(fichier);
    }
    return noeud;
}


int main(void) {
    Arbre arbre_abr, arbre_non_abr;
    
    FILE* f1 = fopen("arbre1.txt", "r");
    if (f1) {
        arbre_abr = lire_arbre(f1);
    }
    fclose(f1);
    
    FILE* f2 = fopen("arbre2.txt", "r");
    if (f2) {
        arbre_non_abr = lire_arbre(f2);
    }
    fclose(f2);

    // Test des fonction sur le parcours infixe d'un arbre
    printf("Test des fonction sur le parcours infixe d'un arbre\n");
    // Il est ABR
    if (est_abr_infixe(arbre_abr)) {
            printf("L'arbre du fichier arbre 1 est ABR\n");
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR\n");
    }
     // Il est pas ABR
    if (est_abr_infixe(arbre_non_abr)) {
            printf("L'arbre du fichier arbre 2 est ABR\n");
    }
    else {
        printf("L'arbre du fichier arbre 2 n'est pas ABR\n");
    }

    // Test des fonction naives
    printf("\nTest des fonction naives\n");
    // Il est ABR
    if (est_abr_naif(arbre_abr)) {
            printf("L'arbre du fichier arbre 1 est ABR\n");
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR\n");
    }
     // Il est pas ABR
    if (est_abr_naif(arbre_non_abr)) {
            printf("L'arbre du fichier arbre 2 est ABR\n");
    }
    else {
        printf("L'arbre du fichier arbre 2 n'est pas ABR\n");
    }

    return 0;
}