#include "Case.h"
#include <iostream>

namespace cases{

    Case::Case(int x, int y) : x(x), y(y), etat(nullptr) {}

    Case::Case(int x, int y, Cellule* etat) : x(x), y(y), etat(etat) {}

    Case::~Case() {
        delete etat;
    }

    int Case::getX() const {
        return x;
    }

    int Case::getY() const {
        return y;
    }

    Cellule* Case::getEtat() const {
        return etat;
    }

    void Case::setEtat(Cellule* nouvelleEtat) {
        delete etat;
        etat = nouvelleEtat;
    }

}