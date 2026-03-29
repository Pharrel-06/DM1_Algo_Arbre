import csv
import matplotlib.pyplot as plt

# Lecture du fichier CSV
def lire_csv(nom_fichier):
    with open(f"{nom_fichier}", newline = '', encoding = 'utf-8') as fichier:
        dico_données = csv.DictReader(fichier, delimiter =';')
        lst_données = [ligne for ligne in dico_données]
    return lst_données

def recup_donnee_temps(methode, morpho, lst_données):
    res_temps = []
    for ligne in lst_données:
        if ligne["Methode"] == methode and ligne["Morphologie"] == morpho:
            res_temps.append(ligne["Temps"])
    return res_temps

def recup_donnee_visite(methode, morpho, lst_données):
    res_visite = []
    for ligne in lst_données:
        if ligne["Methode"] == methode and ligne["Morphologie"] == morpho:
            res_visite.append(ligne["Nb_visites"])
    return res_visite

def trace_courbe(axes, nb_axe_x, nb_axe_y, lst_tailles, lst_données, titre, echelle_y) :
    axes[nb_axe_x, nb_axe_y].plot(lst_tailles, lst_données, label="temps")
    axes[nb_axe_x, nb_axe_y].set_title(titre)
    axes[nb_axe_x, nb_axe_y].set_xlabel("Taille")
    axes[nb_axe_x, nb_axe_y].set_ylabel(echelle_y)
    axes[nb_axe_x, nb_axe_y].legend()

if __name__ == "__main__":
    lst_tailles = [] # Liste du nombre de noeud par test
    lst_methodes = set() # Liste avec le nom de toute les méthode utilisé
    lst_morpho = set()

    lst_données = lire_csv("mesures.csv")

    # Réccupération de toute les tailles et méthodes utilisés
    for ligne in lst_données:
        if ligne["Taille"] not in lst_tailles :
            lst_tailles.append(ligne["Taille"])
        lst_methodes.add(ligne["Methode"])
        lst_morpho.add(ligne["Morphologie"])


    plt.plot(lst_tailles, recup_donnee_temps("naif", "ABR_complet", lst_données), marker='o')
    plt.grid()
    plt.show()
    
    # fig, axes = plt.subplots(2, 3, figsize=(10, 8))


    # # ABR complet
    # for methode in lst_methodes:
    #     trace_courbe(axes, 0, 0, lst_tailles, recup_donnee_temps(methode, "ABR_complet", lst_données), "ABR_complet", "Temps (s)")
    # # non ABR complet
    # for methode in lst_methodes:
    #     trace_courbe(axes, 1, 0, lst_tailles, recup_donnee_temps(methode, "non_ABR_complet", lst_données), "non_ABR_complet", "Temps (s)")

    # # ABR filiforme
    # for methode in lst_methodes:
    #     trace_courbe(axes, 0, 1, lst_tailles, recup_donnee_temps(methode, "ABR_filiforme", lst_données), "ABR_filiforme", "Temps (s)")
    # # non ABR filiforme
    # for methode in lst_methodes:
    #     trace_courbe(axes, 1, 1, lst_tailles, recup_donnee_temps(methode, "non_ABR_filiforme", lst_données), "non_ABR_filiforme", "Temps (s)")

    # # ABR quelconque
    # for methode in lst_methodes:
    #     trace_courbe(axes, 0, 2, lst_tailles, recup_donnee_temps(methode, "ABR_quelconque", lst_données), "ABR_quelconque", "Temps (s)")
    # # non ABR quelconque
    # for methode in lst_methodes:
    #     trace_courbe(axes, 1, 2, lst_tailles, recup_donnee_temps(methode, "non_ABR_quelconque", lst_données), "non_ABR_quelconque", "Temps (s)")
    
    # plt.show()


            




