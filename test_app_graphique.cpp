#include "interface_graphique/App_graphique.h"
#include <iostream>
#include <cstdlib>

int main() {
    try {
        std::string chemin = "test_graphique.txt";
        std::cout << "Création de l'objet Jeu avec chemin : " << chemin << std::endl;
        jeu::Jeu jeu(chemin);

        // Récupération de la grille
        grille::Grille* g = jeu.getGrille();
        int lignes = 0, colonnes = 0;

        if (g && g->getLignes() > 0 && g->getColonnes() > 0) {
            lignes = g->getLignes();
            colonnes = g->getColonnes();
            std::cout << "Grille récupérée : " << lignes << " lignes x " << colonnes << " colonnes." << std::endl;
        } else {
            // Grille invalide -> on crée une grille de test
            lignes = 50;
            colonnes = 50;
            std::cout << "Grille invalide ou vide ! Utilisation d'une grille de test : "
                      << lignes << "x" << colonnes << std::endl;
        }

        // Création de l'application graphique avec des dimensions sûres
        int cellSize = 20;
        app_graphique::App_graphique app(jeu, cellSize, lignes, colonnes);

        // Affichage des dimensions de la fenêtre
        std::cout << "Dimensions fenêtre : " << lignes * cellSize << "x" << colonnes * cellSize << std::endl;

        // Lancement de l'interface graphique
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception attrapée : " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Exception inconnue !" << std::endl;
        return 1;
    }

    return 0;
}
