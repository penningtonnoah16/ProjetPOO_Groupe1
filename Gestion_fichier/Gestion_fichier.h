#pragma once
#include "../Grille/Grille.h"
#include <string>

namespace gestion_fichier {
    class GestionFichier {
    public:
        GestionFichier() = default;
        ~GestionFichier() = default;
        void ecrireGrille(const grille::Grille&, const std::string&, int);
        static std::string creerDossierSortie(const std::string&);
        static Grille::Grille* lireGrille(const std::string&)
    };
}