#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

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

void affiche_prefixe(Arbre a) {
    if (!a) {
        printf("-1 ");
        return;
    }
    printf("%d ", a->valeur);
    affiche_prefixe(a->fg);
    affiche_prefixe(a->fd);
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
    long long visites = 0;
    if (est_abr_infixe(arbre_abr, &visites)) {
            printf("L'arbre du fichier arbre 1 est ABR, visite = %lld\n", visites);
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR, visite = %lld\n", visites);
    }
     // Il est pas ABR
    visites = 0;
    if (est_abr_infixe(arbre_non_abr, &visites)) {
            printf("L'arbre du fichier arbre 1 est ABR, visite = %lld\n", visites);
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR, visite = %lld\n", visites);
    }

    // Test des fonction naives
    printf("\nTest des fonction naives\n");
    visites = 0;
    // Il est ABR
    if (est_abr_naif(arbre_abr, &visites)) {
            printf("L'arbre du fichier arbre 1 est ABR, visite = %lld\n", visites);
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR, visite = %lld\n", visites);
    }

    // Il est pas ABR
    visites = 0;
    if (est_abr_naif(arbre_non_abr, &visites)) {
            printf("L'arbre du fichier arbre 1 est ABR, visite = %lld\n", visites);
    }
    else {
        printf("L'arbre du fichier arbre 1 n'est pas ABR, visite = %lld\n", visites);
    }

    // Test fonction infixe vers préfixe complet
    printf("\nTest de la fonction infixe vers préfixe complet\n");

    int n = 10;
    int* infixe = malloc(sizeof(int) * n);
    int* prefixe = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        infixe[i] = i + 1;
    }
    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, n);
    printf("Parcours préfixe d'un arbre à %d noeuds : ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", prefixe[i]);
    }
    printf("\n");
    
    return 0;
}