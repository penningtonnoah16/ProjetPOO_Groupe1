#include <iostream>
#include "Jeu/Jeu.h"
#include "Gestion_fichier/Gestion_fichier.h"

void afficherGrille(grille::Grille* g)
{
    int L = g->getLignes();
    int C = g->getColonnes();

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            std::cout << (g->estVivante(i,j) ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
}

int main() 
{
    std::cout << "=== TEST : CHARGEMENT DU FICHIER ===\n";

    jeu::Jeu jeu("exemple.txt");
    grille::Grille* g = jeu.getGrille();

    std::cout << "Grille initiale :\n";
    afficherGrille(g);

    std::cout << "\n=== TEST : 1ère ITERATION ===\n";
    jeu.iterer();
    afficherGrille(jeu.getGrille());
    std::cout << "Stable ? " << jeu.estStable() << "\n";

    std::cout << "\n=== TEST : 2ème ITERATION ===\n";
    jeu.iterer();
    afficherGrille(jeu.getGrille());
    std::cout << "Stable ? " << jeu.estStable() << "\n";

    std::cout << "\n=== TEST : 3ème ITERATION ===\n";
    jeu.iterer();
    afficherGrille(jeu.getGrille());
    std::cout << "Stable ? " << jeu.estStable() << "\n";

    std::cout << "\n=== TEST : EXECUTION CONSOLE ===\n";
    jeu.executerConsole(4);
    std::cout << "Dossiers et fichiers Gi générés.\n";

    std::cout << "\n=== TEST : LECTURE D'UN GI ===\n";
    grille::Grille* g2 = gestion_fichier::GestionFichier::lireGrille("exemple.txt_out/grille_2.txt");

    if (g2) {
        std::cout << "Lecture réussie, affichage du fichier grille_2.txt :\n";
        afficherGrille(g2);
    }

    delete g2;

    std::cout << "\n=== FIN DES TESTS ===\n";
    return 0;
}
