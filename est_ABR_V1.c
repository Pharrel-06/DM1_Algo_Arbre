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
    while (a->fg != NULL) 
        a = a->fg; 
    
    return a->valeur; 
} 

int abr_max(Arbre a) { 
    while (a->fd != NULL) 
        a = a->fd; 
    
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

int infixe_croissant(Arbre a, Noeud ** dernier_noeud);

int est_abr_infixe(Arbre a);

int main(void) {
    return 0;
}
