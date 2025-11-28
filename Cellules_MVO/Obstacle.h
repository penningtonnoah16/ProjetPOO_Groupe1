#pragma once 

#include "Cellule.h"

namespace cellules {

    class Obstacle : public Cellule {
    public:
        Obstacle() = default;
        ~Obstacle() = default;
        bool estVivante() const override;
    };

}