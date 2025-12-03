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
            Jeu(const std::string& fichier);
            ~Jeu();

            void charger(const std::string& fichier);
            void setGrille(grille::Grille* g);

            void iterer();
            bool estStable() const;

            void executerConsole(int n);

            grille::Grille* getGrille() const;
    };

}
