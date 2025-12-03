#pragma once

namespace cellules{
    class Cellule {
    
    public:
        virtual bool estVivante() const = 0;
        virtual ~Cellule() = default;
};
    
}