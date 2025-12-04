#pragma once
#include "../Case/Case.h"
#include <vector>

namespace grille {
    class Grille {

        private:
            int lignes;
            int colonnes;
            std::vector<cases::Case*> cases;

            int index(int x, int y) const;

        public:
            Grille(int, int);
            Grille(int, int, const std::vector<int>&);
            ~Grille();

            cases::Case* getCase(int, int) const;
            bool estVivante(int, int) const;
            int compterVoisinsVivants(int, int) const;
            int getLignes() const;
            int getColonnes() const;
    };

}
