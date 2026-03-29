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
    if (*n <= 0) {
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
    if (n <= 1) return 0;

    int puissance = 1;
    int hauteur = 0;
    while (puissance * 2 <= n) {
        puissance *= 2;
        hauteur++;
    }

    int nb_dernier = n - (puissance - 1);
    int max_gauche_dernier = puissance / 2;
    int noeuds_gauche_complet = (puissance / 2) - 1;

    if (nb_dernier >= max_gauche_dernier) {
        return noeuds_gauche_complet + max_gauche_dernier;
    } 
    return noeuds_gauche_complet + nb_dernier;
}

void parcours_infixe_2_prefixe_presque_complet_aux(int ** prefixe, int * infixe, int n) {
    if (n == 0) {
        (**prefixe)  = -1;
        (*prefixe)++;
        return;
    }
    int nb_gauche = nb_noeuds_gauche(n);
    int nb_droite = n - nb_gauche - 1;
    (**prefixe) = infixe[nb_gauche];
    (*prefixe)++;

    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe, nb_gauche);

    parcours_infixe_2_prefixe_presque_complet_aux(prefixe, infixe + nb_gauche + 1, nb_droite);
}

void parcours_infixe_2_prefixe_presque_complet(int * prefixe, int * infixe, int n) {
    int* nouv_prefixe = prefixe;
    parcours_infixe_2_prefixe_presque_complet_aux(&nouv_prefixe, infixe, n);
}

void parcours_infixe_2_prefixe_filiforme_aleatoire_aux(int *prefixe, int *infixe, int n, int* pos) {
    if (n <= 0) {
        prefixe[*pos] = -1;
        (*pos)++;
        return;
    }

    int gauche = rand() % 2;
    int nb_g;
    if (gauche) {
        nb_g = n - 1;
    } else {
        nb_g = 0;
    }

    prefixe[*pos] = infixe[nb_g];
    (*pos)++;

    // Sous-arbre gauche
    parcours_infixe_2_prefixe_filiforme_aleatoire_aux(prefixe, infixe, nb_g, pos);

    // Sous-arbre droit
    parcours_infixe_2_prefixe_filiforme_aleatoire_aux(prefixe, infixe + nb_g + 1, n - nb_g - 1, pos);
}

void parcours_infixe_2_prefixe_filiforme_aleatoire(int *prefixe, int *infixe, int n) {
    int pos = 0;
    parcours_infixe_2_prefixe_filiforme_aleatoire_aux(prefixe, infixe, n, &pos);
}

void parcours_infixe_2_prefixe_quelconque_aleatoire(int *codage, int *infixe, int n) {
    if (!n) {
        codage[0] = -1; 
        return;
    }

    int nb_g = rand() % n;
    codage[0] = infixe[nb_g];

    parcours_infixe_2_prefixe_quelconque_aleatoire(
        codage + 1,
        infixe,
        nb_g
    );

    parcours_infixe_2_prefixe_quelconque_aleatoire(
        codage + 1 + (2 * nb_g + 1),
        infixe + nb_g + 1,
        n - nb_g - 1
    );
}

int ABR_presque_complet_alea(Arbre * a, int taille) {
    //*a = NULL;
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = (int*) malloc(taille * sizeof(int));
    int *prefixe = (int*) malloc(((2 * taille) + 1) * sizeof(int));
    int *prefixe_orig = prefixe;

    if (!infixe || !prefixe) {
        free(infixe);
        free(prefixe);
        return 0;
    }

    // infixe TRIÉ → ABR garanti
    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille);

    int res = construit_quelconque(a, &prefixe, (2 * taille) + 1); 

    free(infixe);
    free(prefixe_orig);

    return res;
}  

int non_ABR_presque_complet_alea(Arbre * a, int taille) {
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = malloc(taille * sizeof(int));
    int *prefixe = malloc((2 * taille + 1) * sizeof(int));
    int *prefixe_orig = prefixe; 

    if (!infixe || !prefixe) {
        free(infixe);
        free(prefixe);
        return 0;
    }

    // tableau trié
    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    // mélange (shuffle intégré)
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = infixe[i];
        infixe[i] = infixe[j];
        infixe[j] = tmp;
    }

    parcours_infixe_2_prefixe_presque_complet(prefixe, infixe, taille);

    int res = construit_quelconque(a, &prefixe, 2 * taille + 1);

    free(infixe);
    free(prefixe_orig);

    return res;
}

int ABR_filiforme_alea(Arbre * a, int taille) {
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = malloc(taille * sizeof(int));
    int *prefixe = malloc(((2 * taille) + 1) * sizeof(int));

    if (!infixe || !prefixe) {
        free(infixe);
        free(prefixe);
        return 0;
    }

    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);

    int *ptr = prefixe;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);

    free(infixe);
    free(prefixe);

    return res;
}

int non_ABR_filiforme_alea(Arbre * a, int taille) {
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = malloc(taille * sizeof(int));
    int *prefixe = malloc((2 * taille + 1) * sizeof(int));

    if (!infixe || !prefixe) {
        free(infixe);
        free(prefixe);
        return 0;
    }

    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = infixe[i];
        infixe[i] = infixe[j];
        infixe[j] = tmp;
    }

    parcours_infixe_2_prefixe_filiforme_aleatoire(prefixe, infixe, taille);

    int *ptr = prefixe;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);

    free(infixe);
    free(prefixe);

    return res;
}

int ABR_quelconque_alea(Arbre * a, int taille) {
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = malloc(taille * sizeof(int));
    int *codage = malloc((2 * taille + 1) * sizeof(int));

    if (!infixe || !codage) return 0;

    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    parcours_infixe_2_prefixe_quelconque_aleatoire(codage, infixe, taille);

    int *ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);

    free(infixe);
    free(codage);

    return res;
}

int non_ABR_quelconque_alea(Arbre * a, int taille) {
    if (taille <= 0) {
        *a = NULL;
        return 1;
    }

    int *infixe = malloc(taille * sizeof(int));
    int *codage = malloc((2 * taille + 1) * sizeof(int));

    if (!infixe || !codage) return 0;

    for (int i = 0; i < taille; i++)
        infixe[i] = i + 1;

    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = infixe[i];
        infixe[i] = infixe[j];
        infixe[j] = tmp;
    }

    parcours_infixe_2_prefixe_quelconque_aleatoire(codage, infixe, taille);

    int *ptr = codage;
    int res = construit_quelconque(a, &ptr, 2 * taille + 1);

    free(infixe);
    free(codage);

    return res;
}