#include "Grille.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Obstacle.h"

namespace grille {

Grille::Grille(int l, int c) : lignes(l), colonnes(c) { // Grille vide initialisée à morte

    cases.resize(lignes * colonnes); // Allouer l'espace pour les cases

    for (int x = 0; x < lignes; x++) {
        for (int y = 0; y < colonnes; y++) {

            cases[index(x, y)] = new cases::Case(x, y, new cellules::Mort()); // Initialiser chaque case à morte
        }
    }
}

Grille::~Grille() {

    for (auto c : cases) delete c;
}

int Grille::index(int x, int y) const {  // Calculer l'index dans le vecteur à partir des coordonnées 2D
    return x * colonnes + y;  // Formule pour convertir les coordonnées 2D en index 1D
}

cases::Case* Grille::getCase(int x, int y) const { // Récupérer une case donnée

    return cases[index(x, y)]; // Utiliser l'index pour accéder à la case
}

bool Grille::estVivante(int x, int y) const {

    return cases[index(x, y)]->getEtat()->estVivante(); // Vérifier si la cellule est vivante
}

int Grille::compterVoisinsVivants(int x, int y) const {
    
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) { // Parcourir les voisins
        for (int dy = -1; dy <= 1; dy++) { // Parcourir les voisins
            if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même si (dx,dy)=(0,0)

            int nx = x + dx; // Coordonnée x du voisin
            int ny = y + dy; // Coordonnée y du voisin

            if (nx >= 0 && nx < lignes &&
                ny >= 0 && ny < colonnes) { // Vérifier les limites

                if (cases[index(nx, ny)]->getEtat()->estVivante()) // Si le voisin est vivant
                    count++;
            }
        }
    }

    return count;
}

Grille::Grille(int l, int c, const std::vector<int>& etats) : lignes(l), colonnes(c) { // Grille initialisée avec des états donnés

    cases.resize(lignes * colonnes); // Allouer l'espace pour les cases

    for (int x = 0; x < lignes; x++) { // Parcourir les lignes
        for (int y = 0; y < colonnes; y++) { // Parcourir les colonnes

            int idx = index(x, y); // Calculer l'index dans le vecteur

            if (etats[idx] == 1){ // Cellule vivante

                cases[idx] = new cases::Case(x, y, new cellules::Vivant());
            }
            else if (etats[idx] == 2){ // Cellule obstacle

                cases[idx] = new cases::Case(x, y, new cellules::Obstacle());
            }
            else { // Cellule morte

                cases[idx] = new cases::Case(x, y, new cellules::Mort());
            }
        }
    }
}

int Grille::getLignes() const { return lignes; }

int Grille::getColonnes() const { return colonnes; }

}
