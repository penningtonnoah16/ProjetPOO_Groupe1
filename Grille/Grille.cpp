#include "Grille.h"
#include "../Cellules_MVO/Mort.h"

namespace grille {

Grille::Grille(int l, int c)
    : lignes(l), colonnes(c)
{
    cases.resize(lignes * colonnes);

    for (int x = 0; x < lignes; x++) {
        for (int y = 0; y < colonnes; y++) {
            cases[index(x, y)] = new cases::Case(x, y, new cellules::Mort());
        }
    }
}

Grille::~Grille() {
    for (auto c : cases) delete c;
}

cases::Case* Grille::getCase(int x, int y) const {
    return cases[index(x, y)];
}

bool Grille::estVivante(int x, int y) const {
    return cases[index(x, y)]->getEtat()->estVivante();
}

int Grille::compterVoisinsVivants(int x, int y) const {
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < lignes &&
                ny >= 0 && ny < colonnes) {

                if (cases[index(nx, ny)]->getEtat()->estVivante())
                    count++;
            }
        }
    }

    return count;
}

Grille(int l, int c, const std::vector<int>& etats)
    : lignes(l), colonnes(c)
{
    cases.resize(lignes * colonnes);

    for (int x = 0; x < lignes; x++) {
        for (int y = 0; y < colonnes; y++) {

            int idx = index(x, y);

            if (etats[idx] == 1)
                cases[idx] = new cases::Case(x, y, new cellules::Vivant());
            else
                cases[idx] = new cases::Case(x, y, new cellules::Mort());
        }
    }
}

int Grille::getLignes() const { return lignes; }
int Grille::getColonnes() const { return colonnes; }

}
