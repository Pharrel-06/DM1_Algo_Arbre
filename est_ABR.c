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

int est_abr_definition_aux(Arbre a, int *min, int *max);

int est_abr_definition(Arbre a);

int infixe_croissant(Arbre a, Noeud ** dernier_noeud);

int est_abr_infixe(Arbre a);
