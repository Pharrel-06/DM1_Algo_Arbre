#include <stdio.h>
#include <stdlib.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

Arbre alloue_noeud(int val) {
    Arbre nouv_noeud = (Arbre) malloc(sizeof(Noeud));
    if (nouv_noeud) {
        nouv_noeud->valeur = val;
        nouv_noeud->fd = NULL;
        nouv_noeud->fg = NULL;
    }
    return nouv_noeud;
}

void detruit_arbre(Arbre * a) {
    if (*a) {
        detruit_arbre(&(*a)->fg);
        detruit_arbre(&(*a)->fd);
        free(*a);
        (*a) = NULL;
    }
}

int construit_quelconque_rec(Arbre * a, int ** codage, int *n) {
    if (*n < 0) {
        
        return 0;
    }

    if ((**codage) == -1) {
        *a = NULL;
        (*codage)++;
        (*n)--;
        return 1;
    }

    *a = alloue_noeud(**codage);

    if (!(*a)) {
        return 0;
    }

    (*codage)++;
    (*n)--;
    int res = construit_quelconque_rec(&((*a)->fg), codage, n);

    if (!res) {
        detruit_arbre(a);
        return 0;
    }

    res = construit_quelconque_rec(&((*a)->fd), codage, n);

    if (!res) {
        detruit_arbre(a);
        return 0;
    }
    return 1;
}

int construit_quelconque(Arbre * a, int ** codage, int n) {
    return construit_quelconque_rec(a, codage, &n);
}

int nb_noeuds_gauche(int n) {
    /* Calcule de la hauteur en faisant des divisions successive par 2 */
    int tmp = n;
    int hauteur = 0;
    while (tmp > 1) {
        tmp /= 2;
        hauteur++;
    }
    /* Calcule du nombre de noeud dans la partie complète de l'arbre */
    int nb_noeud_etage = 0;
    int puissance_de_2 = 1;
    for (int i = 0; i < hauteur; i++) {
        nb_noeud_etage += puissance_de_2;
        puissance_de_2 *= 2;
    }
    /* Calcule du nombre de noeud dans la partie potentiellement imcomplète de l'arbre (dernier étage) */
    int nb_dernier_etage = n - nb_noeud_etage;
    /* Si le nombre de noeud au dernier étage est plus grand que le nombre de noeud max / 2, on renvoie max / 2*/
    if (nb_dernier_etage > puissance_de_2 / 2) {
        return puissance_de_2 / 2 + nb_noeud_etage / 2;
    }
    /* Sinon, on renvoie le nombre de noeud au dernier étage */
    return nb_dernier_etage + nb_noeud_etage / 2;
}

void parcours_infixe_2_prefixe_presque_complet(int * prefixe, int * infixe, int n) {
    int nb_gauche = nb_noeuds_gauche(n);
    int nb_droite = n - nb_gauche - 1;
    prefixe[0] = infixe[nb_gauche];
    if (nb_gauche > 0) {
        parcours_infixe_2_prefixe_presque_complet(prefixe + 1, infixe, nb_gauche);
    }
    if (nb_droite > 0) {
        parcours_infixe_2_prefixe_presque_complet(prefixe + nb_gauche + 1, infixe + nb_gauche + 1, nb_droite);
    }
}

void parcours_infixe_2_prefixe_filiforme_aleatoire(int * prefixe, int * infixe, int n);

void parcours_infixe_2_prefixe_quelconque_aleatoire(int * codage, int * infixe, int n);

int ABR_presque_complet_alea(Arbre * a, int taille);

int non_ABR_presque_complet_alea(Arbre * a, int taille);

int ABR_filiforme_alea(Arbre * a, int taille);

int non_ABR_filiforme_alea(Arbre * a, int taille);

int ABR_quelconque_alea(Arbre * a, int taille);

int non_ABR_quelconque_alea(Arbre * a, int taille);