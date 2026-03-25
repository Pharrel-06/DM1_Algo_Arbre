#ifndef GENERE_ARBRE_BINAIRE_H
#define GENERE_ARBRE_BINAIRE_H

#include "est_ABR.h"

Arbre alloue_noeud(int val);

int construit_quelconque(Arbre * a, int ** codage, int n);

void parcours_infixe_2_prefixe_presque_complet(int * prefixe, int * infixe, int n);

void parcours_infixe_2_prefixe_filiforme_aleatoire(int * prefixe, int * infixe, int n);

void parcours_infixe_2_prefixe_quelconque_aleatoire(int * codage, int * infixe, int n);

int ABR_presque_complet_alea(Arbre * a, int taille);

int non_ABR_presque_complet_alea(Arbre * a, int taille);

int ABR_filiforme_alea(Arbre * a, int taille);

int non_ABR_filiforme_alea(Arbre * a, int taille);

int ABR_quelconque_alea(Arbre * a, int taille);

int non_ABR_quelconque_alea(Arbre * a, int taille);

#endif