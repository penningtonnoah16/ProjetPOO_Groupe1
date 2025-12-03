#pragma once
#include "../Grille/Grille.h"
#include "../Cellules_MVO/Cellule.h"

namespace regles {
    class Regle {

        public:
            virtual ~Regle() = default;
            virtual cellules::Cellule* calculerEtatSuivant(const grille::Grille& g, int x, int y) const = 0;
    };
}
