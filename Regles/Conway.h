#pragma once
#include "Regle.h"

namespace regles {
    class Conway : public Regle {
        
        public:
            cellules::Cellule* calculerEtatSuivant(const grille::Grille& g, int x, int y) const override;
    };

}
