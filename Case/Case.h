#pragma once
#include "../Cellules_MVO/Cellule.h"

namespace cases{

    class Case {
        private :
            cellules::Cellule* etat;
            int x;
            int y;
        public:
            Case(int, int);
            Case(int, int, cellules::Cellule*);
            ~Case();
            int getX() const;
            int getY() const;
            cellules::Cellule* getEtat() const;
            void setEtat(cellules::Cellule*);
    
};
}
