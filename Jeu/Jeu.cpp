#include "Jeu.h"
#include "../Regles/Conway.h"
#include "../Gestion_fichier/Gestion_fichier.h"

namespace jeu {

Jeu::Jeu(const std::string& fichier) : grille(nullptr), regle(new regles::Conway()), fichierEntree(fichier), stable(false) { // Initialiser la grille depuis le fichier s'il est fourni
    
    if (fichier != "") { // Charger la grille depuis le fichier

        grille = gestion_fichier::GestionFichier::lireGrille(fichier); // Lire la grille depuis le fichier
    }
}

Jeu::~Jeu() { // Destructeur pour libérer la mémoire
    
    delete grille;
    delete regle;
}

void Jeu::charger(const std::string& fichier) { // Charger une grille depuis un fichier
    
    fichierEntree = fichier; // Mettre à jour le nom du fichier d'entrée
    delete grille; // Supprimer l'ancienne grille s'il y en a une
    grille = gestion_fichier::GestionFichier::lireGrille(fichier); // Lire la nouvelle grille depuis le fichier
    stable = false; // Réinitialiser le statut de stabilité
}

void Jeu::setGrille(grille::Grille* g) { // Assigner une nouvelle grille au jeu

    if (grille) delete grille; // Supprimer l'ancienne grille s'il y en a une
    grille = g; // Assigner la nouvelle grille
    stable = false; // Réinitialiser le statut de stabilité
}

void Jeu::iterer() {

    int L = grille->getLignes();
    int C = grille->getColonnes();

    auto* nouvelle = new grille::Grille(L, C); // Créer une nouvelle grille pour l'état suivant
    bool identique = true; // Supposer que les grilles sont identiques au début

    for (int i = 0; i < L; i++) { // Parcourir les lignes
        for (int j = 0; j < C; j++) { // Parcourir les colonnes

            cellules::Cellule* next = regle->calculerEtatSuivant(*grille, i, j); // Calculer le nouvel état de la cellule

            bool old = grille->estVivante(i,j); // État actuel de la cellule
            bool ne  = next->estVivante(); // Nouvel état de la cellule

            if (old != ne) identique = false; // Si un état diffère, les grilles ne sont pas identiques

            nouvelle->getCase(i,j)->setEtat(next);
        }
    }

    delete grille; // Supprimer l'ancienne grille
    grille = nouvelle; // Mettre à jour la grille actuelle
    stable = identique; // Mettre à jour le statut de stabilité
}

bool Jeu::estStable() const {
    
    return stable;
}

void Jeu::executerConsole(int n) { // Exécuter la simulation en mode console

    std::string dossier = gestion_fichier::GestionFichier::creerDossierSortie(fichierEntree); // Créer le dossier de sortie

    gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, 0); // Écrire l'état initial

    for (int i = 1; i <= n; i++) { // Itérer n fois

        iterer();
        gestion_fichier::GestionFichier::ecrireGrille(*grille, dossier, i);

        if (stable) { // Si la grille est stable, arrêter la simulation
            
            break;
        }
    }
}

grille::Grille* Jeu::getGrille() const {
    
    return grille;
}

}