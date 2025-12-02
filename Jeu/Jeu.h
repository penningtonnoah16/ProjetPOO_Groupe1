#pragma once
#include "../Grille/Grille.h"
#include "../Regles/Regle.h"
#include <string>

namespace jeu {

class Jeu {
public:
    explicit Jeu(const std::string& cheminEntree);
    ~Jeu();

    void charger(const std::string& path);
    void iterer();
    bool estStable() const;
    void executerConsole(int n);

    grille::Grille* getGrille() const;

private:
    grille::Grille* grille;
    regles::Regle* regle;
    std::string cheminFichierEntree;
    bool stable;
};

}
