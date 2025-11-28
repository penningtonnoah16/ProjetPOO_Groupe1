#include "Case.h"
#include <iostream>

namespace cases{

    Case::Case(int x, int y) : x(x), y(y), etat(nullptr) {}

    Case::Case(int x, int y, cellules::Cellule* etat) : x(x), y(y), etat(etat) {}

    Case::~Case() {
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

    void Case::setEtat(cellules::Cellule* nouvelleEtat) {
        delete etat;
        etat = nouvelleEtat;
    }

}