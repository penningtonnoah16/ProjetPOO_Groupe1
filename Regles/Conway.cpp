#include "Conway.h"
#include "../Grille/Grille.h"
#include "../Case/Case.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"

namespace regles {

    cellules::Cellule* Conway::calculerEtatSuivant(const grille::Grille& g, int x, int y) const {

        cases::Case* c = g.getCase(x, y);
        cellules::Cellule* etat = c->getEtat();

        if (dynamic_cast<cellules::Obstacle*>(etat) != nullptr) {

            return new cellules::Obstacle();
        }

        int voisins = g.compterVoisinsVivants(x, y);
        bool vivante = etat->estVivante();

        if (vivante) {
            if (voisins == 2 || voisins == 3){
                
                return new cellules::Vivant();
            }
            else {

                return new cellules::Mort();
            }
        } 
        else {
            if (voisins == 3){

                return new cellules::Vivant();
            }
            else{
                
                return new cellules::Mort();
            }
        }
    }

}
