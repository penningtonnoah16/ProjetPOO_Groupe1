#include "Case.h"
#include <iostream>

namespace cases{

    Case::Case(int x, int y) : x(x), y(y), etat(nullptr) {} // Initialiser etat à nullptr

    Case::Case(int x, int y, cellules::Cellule* etat) : x(x), y(y), etat(etat) {} // Initialiser avec un état donné

    Case::~Case() { // Destructeur pour libérer la mémoire
        
        delete etat;
    }

    int Case::getX() const {
        
        return x;
    }

    int Case::getY() const {
        
        return y;
    }

    cellules::Cellule* Case::getEtat() const {
        
        return etat;
    }

    void Case::setEtat(cellules::Cellule* nouvelleEtat) { // Mettre à jour l'état de la cellule
        
        delete etat;
        etat = nouvelleEtat;
    }

}