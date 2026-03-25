#ifndef EST_ABR_H
#define EST_ABR_H

typedef struct noeud {
    int valeur;
    struct noeud *fg , *fd;
} Noeud , * Arbre;

int est_abr_naif(Arbre a, long long *nb_visites);

int est_abr_definition_aux(Arbre a, int *min, int *max, long long *nb_visites);

int est_abr_definition(Arbre a, long long *nb_visites);

int infixe_croissant(Arbre a, Noeud ** dernier_noeud, long long *nb_visites);

int est_abr_infixe(Arbre a, long long *nb_visites);

#endif