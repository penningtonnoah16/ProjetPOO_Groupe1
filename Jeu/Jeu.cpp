#include "Jeu.h"
#include "../Gestion_fichier/Gestion_fichier.h"
#include "../Regles/Conway.h"

namespace jeu {

Jeu::Jeu(const std::string& chemin)
    : grille(nullptr),
      regle(new regles::Conway()),
      cheminFichierEntree(chemin),
      stable(false)
{
    grille = gestion_fichier::GestionFichier::lireGrille(chemin);
}

Jeu::~Jeu() {
    delete grille;
    delete regle;
}

void Jeu::charger(const std::string& path) {
    cheminFichierEntree = path;
    delete grille;
    grille = gestion_fichier::GestionFichier::lireGrille(path);
    stable = false;
}

void Jeu::iterer() {
    int lignes   = grille->getLignes();
    int colonnes = grille->getColonnes();

    auto* nouvelle = new grille::Grille(lignes, colonnes);
    bool meme = true;

    for (int x = 0; x < lignes; ++x) {
        for (int y = 0; y < colonnes; ++y) {
            cellules::Cellule* nouveauEtat =
                regle->calculerEtatSuivant(*grille, x, y);

            bool ancienne = grille->estVivante(x, y);
            bool nouvelleVal = nouveauEtat->estVivante();

            if (ancienne != nouvelleVal)
                meme = false;

            nouvelle->getCase(x, y)->setEtat(nouveauEtat);
        }
    }

    delete grille;
    grille = nouvelle;
    stable = meme;
}

bool Jeu::estStable() const {
    return stable;
}

void Jeu::executerConsole(int n) {
    std::string dossier =
        gestion_fichier::GestionFichier::creerDossierSortie(
            cheminFichierEntree + "_out");

    gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, 0);

    for (int i = 1; i <= n; ++i) {
        iterer();
        gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, i);
        if (stable) break;
    }
}

grille::Grille* Jeu::getGrille() const {
    return grille;
}

}
