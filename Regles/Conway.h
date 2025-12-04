#pragma once
#include "Regle.h"

namespace regles {
    class Conway : public Regle {
        
        public:
            cellules::Cellule* calculerEtatSuivant(const grille::Grille&, int, int) const override;
    };

}
