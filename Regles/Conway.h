#include "Règle.h"

namespace conway {
    class Conway : public Règle {
        public : 
            Cellule* calculerEtatSuivant(const Grille&, int, int); 
    }
}