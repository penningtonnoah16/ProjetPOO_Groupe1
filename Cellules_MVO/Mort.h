#pragma once 

#include "Cellule.h"

namespace cellules {
    class Mort : public Cellule {
    
        public:
            Mort() = default;
            ~Mort() = default;
            bool estVivante() const override;
    };

}