#pragma once 
#include "Case.h"
#include <vector>

namespace grille{

    class Grille {
        private :
            int lignes;
            int colonnes;
            vector <vector<Case>> cases;
    public:
        Grille(int, int);
        Case& getCase(int, int);
        bool estvivante(int, int) const;
        int CompterVoisinsVivants(int, int) const;
        int getLignes() const;
        int getColonnes() const;
};
}