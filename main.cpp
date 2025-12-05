#include <iostream>
#include "editeur/editeur.h"
#include "Gestion_fichier/Gestion_fichier.h"
#include "Jeu/Jeu.h"
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"
#include "Cellules_MVO/Obstacle.h"
#include "interface_graphique/App_graphique.h"
#include "test_unitaires/test_unitaires.h"

void afficherMenu() { // Affiche le menu principal
    std::cout << "\n===== MENU PRINCIPAL =====\n";
    std::cout << "1. Charger une grille depuis un fichier\n";
    std::cout << "2. Creer une grille vide (manuelle)\n";
    std::cout << "3. Editer une grille manuellement\n";
    std::cout << "4. Lancer la simulation console\n";
    std::cout << "5. Sauvegarder la grille dans un fichier\n";
    std::cout << "6. Afficher la grille\n";
    std::cout << "7. Lancer l'interface graphique\n";
    std::cout << "8. Réaliser les test unitaires\n";
    std::cout << "9. Quitter\n";
    std::cout << "Votre choix : ";
}

int main() {
    jeu::Jeu* j = nullptr; // Pointeur vers le jeu courant
    bool quitter = false; // Flag pour quitter le programme

    while (!quitter) {
        afficherMenu();
        int choix;
        std::cin >> choix;

        if (choix == 1) {
            std::string path;
            std::cout << "Chemin du fichier à charger : ";
            std::cin >> path; // lire le chemin du fichier

            if (j != nullptr) delete j; //supprimer l'ancien jeu s'il existe
            j = new jeu::Jeu(path); //créer un nouveau jeu avec le fichier
            j->charger(path); //charger la grille depuis le fichier

        }

        else if (choix == 2) {
            int L, C;
            std::cout << "Lignes colonnes : ";
            std::cin >> L >> C; // lire dimensions

            grille::Grille* g = new grille::Grille(L, C);

            if (j != nullptr) delete j;

            j = new jeu::Jeu(""); //créer un nouveau jeu
            j->setGrille(g); //assigner la grille vide au jeu
            std::cout << "Grille vide creee.\n";
        }

        else if (choix == 3) {
            if (j == nullptr) { //vérifier qu'une grille est chargée
                std::cout << "Aucune grille chargee.\n";
            } else {
                editeur::Editeur::lancer(j->getGrille()); //lancer l'éditeur
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
                j->executerConsole(n); //lancer la simulation console
                std::cout << "Simulation terminee.\n";
            }
        }

        else if (choix == 5) {
            if (j == nullptr) {

                std::cout << "Aucune grille a sauvegarder.\n";
            } else {

                std::string fichier; //nom du fichier de sortie
                std::cout << "Nom du fichier a ecrire : ";
                std::cin >> fichier;
                gestion_fichier::GestionFichier::ecrireGrille(*j->getGrille(), fichier, 0); //sauvegarder la grille
                delete j; //supprimer l'ancien jeu
                j=new jeu::Jeu(fichier); //créer un nouveau jeu avec le fichier sauvegardé
                std::cout << "Grille sauvegardee dans " << fichier << "\n";
            }
        }

        else if (choix == 6) {
            if (j == nullptr) {
                std::cout << "Aucune grille a afficher.\n";
            } else {
                grille::Grille* g = j->getGrille(); //récupérer la grille du jeu
                int L = g->getLignes();
                int C = g->getColonnes();

                for (int i = 0; i < L; i++) { //parcourir les lignes
                    for (int j = 0; j < C; j++) { //récupérer chaque cellule
                        cellules::Cellule* cell = g->getCase(i,j)->getEtat(); //afficher son état

                        if (dynamic_cast<cellules::Vivant*>(cell)){ //si vivante

                            std::cout << "1 ";
                        }
                        else if (dynamic_cast<cellules::Obstacle*>(cell)){ //si obstacle

                            std::cout << "2 ";
                        }
                        else { //si morte
                            std::cout << "0 ";
                        }
                    }
                    std::cout << "\n";
                }
            }
        }

        else if (choix == 7) {
            if (j == nullptr) {

                std::cout << "Aucune grille chargee.\n";
            } else {

                int iterations;
                std::cout << "Nombre d'iterations a afficher graphiquement : ";
                std::cin >> iterations;

                app_graphique::App_graphique app(*j, 20);
                app.setDelai(5000);
                app.run(iterations);
            }
        }

        else if (choix ==8) {
            lancerTestsUnitaires();
        }

        else if (choix == 9) {

            quitter = true;
        }

        else {

            std::cout << "Choix invalide.\n";
        }
    }

    delete j;
    return 0;
}
