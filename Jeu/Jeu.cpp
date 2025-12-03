#include "Jeu.h"
#include "../Regles/Conway.h"
#include "../Gestion_fichier/Gestion_fichier.h"

namespace jeu {

Jeu::Jeu(const std::string& fichier) : grille(nullptr), regle(new regles::Conway()), fichierEntree(fichier), stable(false) {
    
    if (fichier != "") {
        
        grille = gestion_fichier::GestionFichier::lireGrille(fichier);
    }
}

Jeu::~Jeu() {
    
    delete grille;
    delete regle;
}

void Jeu::charger(const std::string& fichier) {
    
    fichierEntree = fichier;
    delete grille;
    grille = gestion_fichier::GestionFichier::lireGrille(fichier);
    stable = false;
}

void Jeu::setGrille(grille::Grille* g) {

    if (grille) delete grille;
    grille = g;
}

void Jeu::iterer() {

    int L = grille->getLignes();
    int C = grille->getColonnes();

    auto* nouvelle = new grille::Grille(L, C);
    bool identique = true;

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {

            cellules::Cellule* next = regle->calculerEtatSuivant(*grille, i, j);

            bool old = grille->estVivante(i,j);
            bool ne  = next->estVivante();

            if (old != ne) identique = false;

            nouvelle->getCase(i,j)->setEtat(next);
        }
    }

    delete grille;
    grille = nouvelle;
    stable = identique;
}

bool Jeu::estStable() const {
    
    return stable;
}

void Jeu::executerConsole(int n) {

    std::string dossier = gestion_fichier::GestionFichier::creerDossierSortie(fichierEntree);

    gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, 0);

    for (int i = 1; i <= n; i++) {
        iterer();
        gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, i);
        if (stable) break;
    }
}

grille::Grille* Jeu::getGrille() const {
    
    return grille;
}

}
