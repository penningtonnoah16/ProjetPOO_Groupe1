#include "editeur.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

namespace editeur {

    static void enableRawMode() { // Activer le mode raw pour la saisie clavier

        termios term; // Structure pour les attributs du terminal
        tcgetattr(STDIN_FILENO, &term); // Récupérer les attributs actuels
        term.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'écho
        tcsetattr(STDIN_FILENO, TCSANOW, &term); // Appliquer les nouveaux attributs
    }

    static void disableRawMode() { // Désactiver le mode raw

        termios term; // Structure pour les attributs du terminal
        tcgetattr(STDIN_FILENO, &term); // Récupérer les attributs actuels
        term.c_lflag |= (ICANON | ECHO); // Réactiver le mode canonique et l'écho
        tcsetattr(STDIN_FILENO, TCSANOW, &term); // Appliquer les nouveaux attributs
    }

    static void afficher(grille::Grille* g, int cx, int cy) { // Afficher la grille avec le curseur

        int L = g->getLignes();
        int C = g->getColonnes();

        for (int i = 0; i < L; i++) { // Parcourir les lignes
            for (int j = 0; j < C; j++) { // Parcourir les colonnes

                if (i == cx && j == cy) { // Position du curseur
                    std::cout << "~ ";
                    continue;
                }

                cellules::Cellule* cell = g->getCase(i,j)->getEtat(); // Récupérer l'état de la cellule

                if (dynamic_cast<cellules::Vivant*>(cell)){ // Cellule vivante

                    std::cout << "1 ";
                }
                else if (dynamic_cast<cellules::Obstacle*>(cell)){ // Cellule obstacle

                    std::cout << "2 ";
                }
                else { // Cellule morte

                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }

    void Editeur::lancer(grille::Grille* g) { // Lancer l'éditeur de grille

        int L = g->getLignes();
        int C = g->getColonnes();
        int x = 0, y = 0;

        enableRawMode();

        while (true) {

            std::cout << "\033[H\033[J"; // Effacer l'écran
            std::cout << "EDITEUR : fleches = bouger | espace = changer | q = quitter\n\n";

            afficher(g, x, y); // Afficher la grille

            char c = getchar(); // Lire un caractère

            if (c == 'q') {

                break;
            };

            if (c == 27) { // Séquence d'échappement pour les flèches

                char c1 = getchar();
                char c2 = getchar();
                    
                if (c1 == '[') { // Indicateur de flèche

                    if (c2 == 'A') x--; // Flèche haut
                    if (c2 == 'B') x++; // Flèche bas
                    if (c2 == 'C') y++; // Flèche droite
                    if (c2 == 'D') y--; // Flèche gauche

                    if (x < 0) x = 0;
                    if (x >= L) x = L - 1;
                    if (y < 0) y = 0;
                    if (y >= C) y = C - 1;
                }
            }

            if (c == ' ') { // Espace pour changer l'état de la cellule

                cellules::Cellule* cell = g->getCase(x,y)->getEtat();

                if (dynamic_cast<cellules::Mort*>(cell)){

                    g->getCase(x,y)->setEtat(new cellules::Vivant());
                }
                else if (dynamic_cast<cellules::Vivant*>(cell)){

                    g->getCase(x,y)->setEtat(new cellules::Obstacle());
                }
                else {

                    g->getCase(x,y)->setEtat(new cellules::Mort());
                }
            }
        }

        disableRawMode();
    }
}
