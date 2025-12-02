#pragma once
#include "../Grille/Grille.h"
#include <string>

namespace gestion_fichier {
    class GestionFichier {
    public:
        GestionFichier() = default;
        ~GestionFichier() = default;
        static void ecrireGrille(const grille::Grille&, const std::string&, int);
        static std::string creerDossierSortie(const std::string&);
        static grille::Grille* lireGrille(const std::string&);
    };
}