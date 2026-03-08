#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"

Arbre alloue_noeud(int val) {
    Arbre nouv_noeud = (Arbre) malloc(sizeof(Noeud));
    if (nouv_noeud) {
        nouv_noeud->valeur = val;
        nouv_noeud->fd = NULL;
        nouv_noeud->fg = NULL;
    }
    return nouv_noeud;
}

int abr_min(Arbre a) {
    if (a == NULL)
        return 0;  

    while (a->fg != NULL) { 
        a = a->fg;
    }
      
    return a->valeur;
}

int abr_max(Arbre a) {
    if (a == NULL)
        return 0;

    while (a->fd != NULL) {
        a = a->fd;
    }
     
    return a->valeur;
}

int est_abr_naif(Arbre a) {

    if (a == NULL)
        return 1;

    if (a->fg != NULL && abr_max(a->fg) >= a->valeur)
        return 0;

    if (a->fd != NULL && abr_min(a->fd) <= a->valeur)
        return 0;

    return est_abr_naif(a->fg) && est_abr_naif(a->fd);
}

int est_abr_definition_aux(Arbre a, int *min, int *max);

int est_abr_definition(Arbre a);

int infixe_croissant(Arbre a, Noeud ** dernier_noeud) {
    // Si l'arbre est vide, c'est un ABR
    if (!a) {
        return 1; 
    }
    // Si l'élément actuel est le plus en bas à gauche de l'arbre, on peut initialiser dernier_noeud pour le parcour infixe
    if (!(*dernier_noeud) && !(a->fg)) {
        *dernier_noeud = a;
        // On renvoie le résultat de la vérification du fd
        return infixe_croissant(a->fd, dernier_noeud);
    }
    // Si le sous arbre gauche n'est pas un ABR, l'arbre actuel ne l'est pas non plus
    if (!infixe_croissant(a->fg, dernier_noeud)) {
        return 0;
    }
    // A partir d'ici, dernier_noeud est forcément initialisé
    // Si le noeud précédent dans le parcours infixe est plus grand que le noeud actuel, on est pas ABR
    if ((*dernier_noeud)->valeur >= a->valeur) {
        return 0;
    }
    // On met à jour dernier noeud dans le parcours infixe
    *dernier_noeud = a;
    // Si le sous arbre droit est ABR, l'arbre actuel est ABR
    return infixe_croissant(a->fd, dernier_noeud);
}

int est_abr_infixe(Arbre a) {
    Noeud* dernier_noeud = NULL;
    return infixe_croissant(a, &dernier_noeud);
}

