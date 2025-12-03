#include "editeur.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

namespace editeur {

    static void enableRawMode() {

        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }

    static void disableRawMode() {

        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }

    static void afficher(grille::Grille* g, int cx, int cy) {

        int L = g->getLignes();
        int C = g->getColonnes();

        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C; j++) {

                if (i == cx && j == cy) {
                    std::cout << "~ ";
                    continue;
                }

                cellules::Cellule* cell = g->getCase(i,j)->getEtat();

                if (dynamic_cast<cellules::Vivant*>(cell)){

                    std::cout << "1 ";
                }
                else if (dynamic_cast<cellules::Obstacle*>(cell)){

                    std::cout << "2 ";
                }
                else {

                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }

    void Editeur::lancer(grille::Grille* g) {

        int L = g->getLignes();
        int C = g->getColonnes();
        int x = 0, y = 0;

        enableRawMode();

        while (true) {

            std::cout << "\033[H\033[J";
            std::cout << "EDITEUR : fleches = bouger | espace = changer | q = quitter\n\n";

            afficher(g, x, y);

            char c = getchar();

            if (c == 'q') {

                break;
            };

            if (c == 27) {

                char c1 = getchar();
                char c2 = getchar();
                    
                if (c1 == '[') {

                    if (c2 == 'A') x--;
                    if (c2 == 'B') x++;
                    if (c2 == 'C') y++;
                    if (c2 == 'D') y--;

                    if (x < 0) x = 0;
                    if (x >= L) x = L - 1;
                    if (y < 0) y = 0;
                    if (y >= C) y = C - 1;
                }
            }

            if (c == ' ') {

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
