#pragma once
#include "../Grille/Grille.h"
#include "../Regles/Regle.h"
#include <string>

namespace jeu {

    class Jeu {

        private:
            grille::Grille* grille;
            regles::Regle* regle;
            std::string fichierEntree;
            bool stable;

        public:
            Jeu(const std::string&);
            ~Jeu();

            void charger(const std::string&);
            void setGrille(grille::Grille*);

            void iterer();
            bool estStable() const;

            void executerConsole(int);

            grille::Grille* getGrille() const;
    };

}
