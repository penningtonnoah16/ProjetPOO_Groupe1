#pragma once 

#include "Cellule.h"

namespace cellules {

    class Vivant : public Cellule {
    public:
        Vivant() = default;
        ~Vivant() = default;
        bool estVivante() const override;
    };

}