import csv
import matplotlib.pyplot as plt

# Lecture du fichier CSV
def lire_csv(nom_fichier):
    with open(f"{nom_fichier}", newline = '', encoding = 'utf-8') as fichier:
        dico_données = csv.DictReader(fichier, delimiter =';')
        lst_données = [ligne for ligne in dico_données]
    return lst_données

def recup_donnee_temps(methode, morpho, lst_donnees):
    res_temps = []
    for ligne in lst_donnees:
        if ligne["Methode"] == methode and ligne["Morphologie"] == morpho:
            res_temps.append(ligne["Temps"])
    return res_temps

def recup_donnee_visite(methode, morpho, lst_donnees):
    res_visite = []
    for ligne in lst_donnees:
        if ligne["Methode"] == methode and ligne["Morphologie"] == morpho:
            res_visite.append(ligne["Nb_visites"])
    return res_visite

def trace_courbes_temps(ax, ax_ligne, ax_colonne, morpho, lst_donnees):
    
    données = recup_donnee_temps("naif", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="naif")
    
    données = recup_donnee_temps("definition", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="definition")

    données = recup_donnee_temps("infixe", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="infixe")

    ax[ax_ligne, ax_colonne].xaxis.set_major_locator(plt.MaxNLocator(8))
    ax[ax_ligne, ax_colonne].yaxis.set_major_locator(plt.MaxNLocator(6))
    
    ax[ax_ligne, ax_colonne].set_xlabel("Taille")
    ax[ax_ligne, ax_colonne].set_ylabel("Temps en ms")

    ax[ax_ligne, ax_colonne].legend()
    ax[ax_ligne, ax_colonne].grid()

    ax[ax_ligne, ax_colonne].set_title(morpho)

def trace_courbes_visite(ax, ax_ligne, ax_colonne, morpho, lst_donnees):
    
    données = recup_donnee_visite("naif", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="naif")
    
    données = recup_donnee_visite("definition", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="definition")

    données = recup_donnee_visite("infixe", morpho, lst_donnees)
    ax[ax_ligne, ax_colonne].plot(lst_tailles, données, marker='o', label="infixe")

    ax[ax_ligne, ax_colonne].xaxis.set_major_locator(plt.MaxNLocator(8))
    ax[ax_ligne, ax_colonne].yaxis.set_major_locator(plt.MaxNLocator(6))
    
    ax[ax_ligne, ax_colonne].set_xlabel("Taille")
    ax[ax_ligne, ax_colonne].set_ylabel("Nb visite")

    ax[ax_ligne, ax_colonne].legend()
    ax[ax_ligne, ax_colonne].grid()

    ax[ax_ligne, ax_colonne].set_title(morpho)


if __name__ == "__main__":
    lst_tailles = [] # Liste du nombre de noeud par test
    lst_methodes = set() # Liste avec le nom de toute les méthode utilisé
    lst_morpho = set()

    lst_donnees = lire_csv("mesures.csv")

    # Réccupération de toute les tailles et méthodes utilisés
    for ligne in lst_donnees:
        if ligne["Taille"] not in lst_tailles :
            lst_tailles.append(ligne["Taille"])
        lst_methodes.add(ligne["Methode"])
        lst_morpho.add(ligne["Morphologie"])

    fig, ax = plt.subplots(2, 3, figsize=(12, 8))
    
    trace_courbes_temps(ax, 0, 0, "ABR_complet", lst_donnees)
    trace_courbes_temps(ax, 0, 1, "ABR_filiforme", lst_donnees)
    trace_courbes_temps(ax, 0, 2, "ABR_quelconque", lst_donnees)

    trace_courbes_visite(ax, 1, 0, "ABR_complet", lst_donnees)
    trace_courbes_visite(ax, 1, 1, "ABR_filiforme", lst_donnees)
    trace_courbes_visite(ax, 1, 2, "ABR_quelconque", lst_donnees)

    plt.tight_layout()
    plt.subplots_adjust(hspace=0.4, wspace=0.3)

    plt.show()
    
    

