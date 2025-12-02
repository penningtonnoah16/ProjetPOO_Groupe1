#include "Conway.h"
#include "Grille.h"
#include "Cellule.h"

namespace conway {
    Cellule* calculerEtatSuivant(const Grille&, int x, int y){
        int compteur_temp = Grille.compterVoisinsVivants(Grille&);

        if (Cellule.estVivant() == 0){
            if (compteur_temp == 2 | compteur_temp == 3){
                return 0;
            }
            return 1;
        }
        if (Cellule.estVivant() == 1){
            if (compteur_temp == 3){
                return 0;
            }
            return 1;

        }
    }
}