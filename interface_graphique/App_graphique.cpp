#include "App_graphique.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"

namespace app_graphique {

    // L'ordre dans la liste correspond à l'ordre des membres dans la classe
    App_graphique::App_graphique(jeu::Jeu& j, int cell, int height, int width)
        : cellSize(cell), gridHeight(height), gridWidth(width), jeu(j) {}

    void App_graphique::render(sf::RenderWindow &window) {
    grille::Grille* g = jeu.getGrille();
    if (!g) return;

    int lignes = g->getLignes();
    int colonnes = g->getColonnes();

    window.clear();

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < lignes; ++x) {
        for (int y = 0; y < colonnes; ++y) {
            cases::Case* c = g->getCase(x, y);
            if (!c) continue;

            // Couleurs selon l'état de la cellule
            int etat = c->getEtat()->estVivante(); // méthode qui renvoie 0,1 ou 2
            if (etat == 1)
                cell.setFillColor(sf::Color::White);       // cellule morte
            else if (etat == 0)
                dynamic_cast<cellules::Mort*>(etat) ? cell.setFillColor(sf::Color::Black) : cell.setFillColor(sf::Color::Red)
                cell.setFillColor(sf::Color::White);       // cellule vivante
                   // troisième état

            cell.setPosition(x * cellSize, y * cellSize);
            window.draw(cell);
        }
    }

    window.display();
}


    void App_graphique::run() {
        grille::Grille& g = *(jeu.getGrille());
        int lignes = g.getLignes();
        int colonnes = g.getColonnes();
        window.create(sf::VideoMode(lignes * cellSize, colonnes * cellSize), "Jeu de la vie");
    

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            render(window);
        }
    }

}
