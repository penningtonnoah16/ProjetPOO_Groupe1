#include <iostream>
#include "editeur/editeur.h"
#include "Gestion_fichier/Gestion_fichier.h"
#include "Jeu/Jeu.h"
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"
#include "Cellules_MVO/Obstacle.h"

void afficherMenu() {
    std::cout << "\n===== MENU PRINCIPAL =====\n";
    std::cout << "1. Charger une grille depuis un fichier\n";
    std::cout << "2. Creer une grille vide (manuelle)\n";
    std::cout << "3. Editer une grille manuellement\n";
    std::cout << "4. Lancer la simulation console\n";
    std::cout << "5. Sauvegarder la grille dans un fichier\n";
    std::cout << "6. Afficher la grille\n";
    std::cout << "7. Quitter\n";
    std::cout << "Votre choix : ";
}

int main() {
    jeu::Jeu* j = nullptr;
    bool quitter = false;

    while (!quitter) {
        afficherMenu();
        int choix;
        std::cin >> choix;

        if (choix == 1) {
            std::string path;
            std::cout << "Chemin du fichier à charger : ";
            std::cin >> path;

            if (j != nullptr) delete j;
            j = new jeu::Jeu(path);
            j->charger(path);

        }

        else if (choix == 2) {
            int L, C;
            std::cout << "Lignes colonnes : ";
            std::cin >> L >> C;

            grille::Grille* g = new grille::Grille(L, C);

            if (j != nullptr) delete j;

            j = new jeu::Jeu("");
            j->setGrille(g);
            std::cout << "Grille vide creee.\n";
        }

        else if (choix == 3) {
            if (j == nullptr) {
                std::cout << "Aucune grille chargee.\n";
            } else {
                editeur::Editeur::lancer(j->getGrille());
                j->setGrille(j->getGrille());
                std::cout << "Edition terminee.\n";
            }
        }

        else if (choix == 4) {
            if (j == nullptr) {
                std::cout << "Aucune grille chargee.\n";
            } else {
                int n;
                std::cout << "Nombre d'iterations : ";
                std::cin >> n;
                j->executerConsole(n);
            }
        }

        else if (choix == 5) {
            if (j == nullptr) {
                std::cout << "Aucune grille a sauvegarder.\n";
            } else {
                std::string fichier;
                std::cout << "Nom du fichier a ecrire : ";
                std::cin >> fichier;
                gestion_fichier::GestionFichier::ecrireGrille(*j->getGrille(), fichier, 0);
                j=new jeu::Jeu(fichier);
                std::cout << "Grille sauvegardee dans " << fichier << "\n";
            }
        }

        else if (choix == 6) {
            if (j == nullptr) {
                std::cout << "Aucune grille a afficher.\n";
            } else {
                grille::Grille* g = j->getGrille();
                int L = g->getLignes();
                int C = g->getColonnes();

                for (int i = 0; i < L; i++) {
                    for (int j = 0; j < C; j++) {
                        cellules::Cellule* cell = g->getCase(i,j)->getEtat();

                        if (dynamic_cast<cellules::Vivant*>(cell))
                            std::cout << "1 ";
                        else if (dynamic_cast<cellules::Obstacle*>(cell))
                            std::cout << "2 ";
                        else
                            std::cout << "0 ";
                    }
                    std::cout << "\n";
                }
            }
        }

        else if (choix == 7) {
            quitter = true;
        }

        else {
            std::cout << "Choix invalide.\n";
        }
    }

    delete j;
    return 0;
}
