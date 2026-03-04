#ifndef GENERE_ARBRE_BINAIRE_H
#define GENERE_ARBRE_BINAIRE_H

#include "est_ABR.h"

int construit_presque_complet(Arbre * a, int ** src, int n);

int construit_filiforme(Arbre * a, int ** src, char ** forme, int n);

int construit_quelconque(Arbre * a, int ** codage, int n);

int ABR_presque_complet_alea(Arbre * a, int taille);

int non_ABR_presque_complet_alea(Arbre * a, int taille);

int ABR_filiforme_alea(Arbre * a, int taille);

int non_ABR_filiforme_alea(Arbre * a, int taille);

int ABR_quelconque_alea(Arbre * a, int taille);

int non_ABR_quelconque_alea(Arbre * a, int taille);

#endif