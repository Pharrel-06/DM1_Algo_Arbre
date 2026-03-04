#ifndef EST_ABR_H
#define EST_ABR_H

typedef struct noeud {
    int valeur;
    struct noeud *fg , *fd;
} Noeud , * Arbre;

Arbre alloue_noeud(int val);

int est_abr_naif(Arbre a);

int est_abr_definition_aux(Arbre a, int *min, int *max);

int est_abr_definition(Arbre a);

int infixe_croissant(Arbre a, Noeud ** dernier_noeud);

int est_abr_infixe(Arbre a);

#endif