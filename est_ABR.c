#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"

int abr_min(Arbre a, long long *nb_visites) {
    if (a == NULL)
        return 0;  

    while (a->fg != NULL) {
        (*nb_visites)++;   
        a = a->fg;
    }

    (*nb_visites)++;       
    return a->valeur;
}

int abr_max(Arbre a, long long *nb_visites) {
    if (a == NULL)
        return 0;

    while (a->fd != NULL) {
        (*nb_visites)++;   
        a = a->fd;
    }

    (*nb_visites)++;       
    return a->valeur;
}

int est_abr_naif(Arbre a, long long *nb_visites) {

    if (a == NULL)
        return 1;

    (*nb_visites)++;  

    if (a->fg != NULL && abr_max(a->fg, nb_visites) >= a->valeur)
        return 0;

    if (a->fd != NULL && abr_min(a->fd, nb_visites) <= a->valeur)
        return 0;

    return est_abr_naif(a->fg, nb_visites) && est_abr_naif(a->fd, nb_visites);
}

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites){
    if (!a) return 1;

    (*nb_visites)++;

    int min_g, max_g, min_d, max_d;
    if (!est_abr_definition_aux(a->fg, &min_g, &max_g, nb_visites)) return 0;
    if (!est_abr_definition_aux(a->fd, &min_d, &max_d, nb_visites)) return 0;

    if (a->fg && max_g >= a->valeur) return 0;
    if (a->fd && min_d <= a->valeur) return 0;

    *min = a->fg ?  min_g : a->valeur;
    *max = a->fd ?  max_d : a->valeur; 
    return 1; 
}

int est_abr_definition(Arbre a, long long *nb_visites){
    int min, max;
    return est_abr_definition_aux(a, &min, &max, nb_visites); 
}

int infixe_croissant(Arbre a, Noeud ** dernier_noeud, long long * nb_visites) {
    // Si l'arbre est vide, c'est un ABR
    if (!a) {
        return 1; 
    }
    (*nb_visites)++;
    // Si l'élément actuel est le plus en bas à gauche de l'arbre, on peut initialiser dernier_noeud pour le parcour infixe
    if (!(*dernier_noeud) && !(a->fg)) {
        *dernier_noeud = a;
        // On renvoie le résultat de la vérification du fd
        return infixe_croissant(a->fd, dernier_noeud, nb_visites);
    }
    // Si le sous arbre gauche n'est pas un ABR, l'arbre actuel ne l'est pas non plus
    if (!infixe_croissant(a->fg, dernier_noeud, nb_visites)) {
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
    return infixe_croissant(a->fd, dernier_noeud, nb_visites);
}

int est_abr_infixe(Arbre a, long long * nb_visites) {
    Noeud* dernier_noeud = NULL;
    return infixe_croissant(a, &dernier_noeud, nb_visites);
}
