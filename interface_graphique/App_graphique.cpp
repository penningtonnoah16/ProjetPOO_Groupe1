#include "App_graphique.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"
#include <iostream>

namespace app_graphique {

    App_graphique::App_graphique(jeu::Jeu& j, int cell) : cellSize(cell), jeu(j) {}

    void App_graphique::setDelai(int ms) { 

        this->delaiMs = ms; 
    }

    void App_graphique::render() { // Dessine la grille actuelle
        grille::Grille* g = jeu.getGrille();
        if (!g) return; // Vérifier que la grille existe

        int lignes = g->getLignes();
        int colonnes = g->getColonnes();

        window.clear(sf::Color(200, 200, 200));

        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1)); // Taille de chaque cellule

        float offsetX = (window.getSize().x - colonnes * cellSize) / 2.0f; // Centrage horizontal
        float offsetY = (window.getSize().y - lignes * cellSize) / 2.0f; // Centrage vertical

        for (int i = 0; i < lignes; ++i) { // Parcourir les lignes
            for (int j = 0; j < colonnes; ++j) { // Parcourir les colonnes

                cellules::Cellule* etat = g->getCase(i, j)->getEtat(); // Récupérer l'état de la cellule

                if (dynamic_cast<cellules::Vivant*>(etat)){ // Cellule vivante

                    cell.setFillColor(sf::Color::Black);
                }
                else if (dynamic_cast<cellules::Obstacle*>(etat)){ // Cellule obstacle

                    cell.setFillColor(sf::Color::Red);
                }
                else { // Cellule morte

                    cell.setFillColor(sf::Color::White);
                }

                cell.setPosition(offsetX + j * cellSize, offsetY + i * cellSize); // Positionner la cellule
                window.draw(cell); // Dessiner la cellule
            }
        }

        window.display(); // Afficher le contenu dessiné
    }


    void App_graphique::run(int iterations) { // Lancer la simulation graphique

        // Fermer la fenêtre si elle était déjà ouverte
        if (window.isOpen()) {
            window.close();
        }

        grille::Grille* g = jeu.getGrille();
        if (!g) return;

        int lignes = g->getLignes();
        int colonnes = g->getColonnes();

        // Créer la fenêtre
        window.create(
            sf::VideoMode(std::max(800, colonnes * cellSize), std::max(600, lignes * cellSize)),
            "Jeu de la Vie - Simulation graphique"
        );

        sf::Clock clock; // Horloge pour gérer le délai entre les itérations
        int currentIteration = 0; // Compteur d'itérations

        while (window.isOpen() && currentIteration < iterations) { // Boucle principale de la fenêtre

            sf::Event event; // Gérer les événements

            while (window.pollEvent(event)) { // Parcourir les événements
                if (event.type == sf::Event::Closed) { // Fermer la fenêtre

                    window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { // Echap

                    window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && delaiMs == 9999) { // Espace pour itérer manuellement

                    jeu.iterer();   // Itérer la grille
                    currentIteration++;// Incrémenter le compteur
                    clock.restart(); // Redémarrer l'horloge
                }
            }
            if (delaiMs != 9999){
                if (clock.getElapsedTime().asMilliseconds() > delaiMs) { // Vérifier le délai

                    jeu.iterer();
                    currentIteration++;
                    clock.restart();
                }
            }

            if (jeu.estStable()) { // Arrêter si la grille est stable

                window.close();
            }

            render();
        }

        // S'assurer que la fenêtre est bien fermée à la fin
        if (window.isOpen()) {
            
            window.close();
        }
    }

}
