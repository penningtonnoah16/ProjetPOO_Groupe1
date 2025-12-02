#include "Jeu.h"
#include <string>
#include "Gestion_fichier.h"
#include "Grille.h"

namespace jeu {
    void charger(std::string){
        grille = Gestion_fichier.lireGrille(cheminFichierEntree);
        stable = 0;
    }



    void iterer(){
        int taille = Grille::get_lignes() * Grille::get_colonnes();
        int i = 0;
        vector<int> grille_temp;
        for (i<taille){
            i++
            grille_temp.push_back(Conway::calculerEtatSuivant(grille, i%get_colonnes(), i/get_lignes()));
        }
    }



    bool estStable(){
        if(grille == Gestion_fichier::lireGrille(cheminFichierEntree)){
            return 1;
        }
        return 0;
    }



    void executerConsole(int iteration){
        grille = Gestion_fichier::lireGrille();
        std::string dossier = Gestion_fichier::creerDossierSortie();
        int i = 0;
        for (i<iteration){
            i++;
            Gestion_fichier::ecrireGrille(grille, dossier, i);
            if (estStable == 1){
                i = iteration;
            }
        }
    }



    const Grille& get_Grille(){
        std::cout << grille << std::endl;
    }
}