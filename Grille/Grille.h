#pragma once
#include "../Case/Case.h"
#include <vector>

namespace grille {
    class Grille {

        private:
            int lignes;
            int colonnes;
            std::vector<cases::Case*> cases;

            int index(int x, int y) const { return x * colonnes + y; }

        public:
            Grille(int l, int c);
            Grille(int, int, const std::vector<int>&);
            ~Grille();

            cases::Case* getCase(int x, int y) const;
            bool estVivante(int x, int y) const;
            int compterVoisinsVivants(int x, int y) const;
            int getLignes() const;
            int getColonnes() const;
    };

}
