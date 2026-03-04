#include <stdio.h>
#include "est_ABR.h"

int est_abr_naif(Arbre a);

int est_abr_definition_aux(Arbre a, int *min, int *max);

int est_abr_definition(Arbre a);

int infixe_croissant(Arbre a, Noeud ** dernier_noeud);

int est_abr_infixe(Arbre a);

int main(void) {
    return 0;
}
