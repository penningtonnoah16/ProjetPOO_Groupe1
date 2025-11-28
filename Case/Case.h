#pragma once
#include "Cellule.h"

namespace cases{

    class Case {
        private :
            Cellule* etat;
            int x;
            int y;
        public:
            Case(int, int);
            Case(int, int, Cellule*);
            ~Case();
            int getX() const;
            int getY() const;
            Cellule* getEtat() const;
            void setEtat(Cellule*);
    
};
}
