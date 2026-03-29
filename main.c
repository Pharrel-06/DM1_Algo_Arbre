#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "est_ABR.h"
#include "genere_arbre_binaire.h"

#define NB_TESTS 1000

void ecrit_mesure(FILE* f, int taille, char* morpho, char* methode, long long nb_visite, double temps) {
    fprintf(f, "%d;%s;%s;%lld;%.3f\n", taille, morpho, methode, nb_visite, temps);
}

void test_performance(FILE* f, Arbre a, int taille, char* morpho) {
    long long nb_visite = 0;
    double temps;

    // Naif
    clock_t debut = clock();
    for (int i = 0;  i < NB_TESTS; i++) {
        est_abr_naif(a, &nb_visite);
    }
    clock_t fin = clock();
    temps = ((double)(fin - debut) * 1000.0) / NB_TESTS;
    ecrit_mesure(f, taille, morpho, "naif", nb_visite / NB_TESTS, temps);

    // Définition
    nb_visite = 0;
    debut = clock();
    for (int i = 0;  i < NB_TESTS; i++) {
        est_abr_definition(a, &nb_visite);
    }
    fin = clock();
    temps = ((double)(fin - debut) * 1000.0) / NB_TESTS;
    ecrit_mesure(f, taille, morpho, "definition", nb_visite / NB_TESTS, temps);

    // Infixe
    nb_visite = 0;
    debut = clock();
    for (int i = 0;  i < NB_TESTS; i++) {
        est_abr_infixe(a, &nb_visite);
    }
    fin = clock();
    temps = ((double)(fin - debut) * 1000.0) / NB_TESTS;
    ecrit_mesure(f, taille, morpho, "infixe", nb_visite / NB_TESTS, temps);
}

int main(void) {

    FILE* fichier = fopen("mesures.csv", "w");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du csv\n");
        return 0;
    }

    fprintf(fichier, "Taille;Morphologie;Methode;Nb_visites;Temps\n");

    srand(time(NULL));
    Arbre abr_complet = NULL;
    Arbre non_abr_complet = NULL;
    Arbre abr_fil = NULL;
    Arbre non_abr_fil = NULL;
    Arbre abr_quelc = NULL;
    Arbre non_abr_quelc = NULL;

    int nb_taille = 51;
    int tailles[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
                    120, 140, 160, 180, 200, 250, 300, 350, 400, 450, 
                    500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 
                    1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 
                    2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 
                    30000};

    for (int i = 0; i < nb_taille; i++) {
        // ABR complet
        if (ABR_presque_complet_alea(&abr_complet, tailles[i])) {
            test_performance(fichier, abr_complet, tailles[i], "ABR_complet");
            detruit_arbre(&abr_complet);
            abr_complet = NULL;
        }
        // non ABR complet
        if (non_ABR_presque_complet_alea(&non_abr_complet, tailles[i])) {
            test_performance(fichier, non_abr_complet, tailles[i], "non_ABR_complet");
            detruit_arbre(&non_abr_complet);
            non_abr_complet = NULL;
        }
        // ABR filiforme
        if (ABR_filiforme_alea(&abr_fil, tailles[i])) {
            test_performance(fichier, abr_fil, tailles[i], "ABR_filiforme");
            detruit_arbre(&abr_fil);
            abr_fil = NULL;
        }
        // non ABR filiforme
        if (non_ABR_filiforme_alea(&non_abr_fil, tailles[i])) {
            test_performance(fichier, non_abr_fil, tailles[i], "non_ABR_filiforme");
            detruit_arbre(&non_abr_fil);
            non_abr_fil = NULL;
        }
        // ABR quelconque
        if (ABR_quelconque_alea(&abr_quelc, tailles[i])) {
            test_performance(fichier, abr_quelc, tailles[i], "ABR_quelconque");
            detruit_arbre(&abr_quelc);
            abr_quelc = NULL;
        }
        // non ABR quelconque
        if (non_ABR_quelconque_alea(&non_abr_quelc, tailles[i])) {
            test_performance(fichier, non_abr_quelc, tailles[i], "non_ABR_quelconque");
            detruit_arbre(&non_abr_quelc);
            non_abr_quelc = NULL;
        }
        printf("Test fini pour taille %d\n", tailles[i]);
    }

    fclose(fichier);

    return 0;
}