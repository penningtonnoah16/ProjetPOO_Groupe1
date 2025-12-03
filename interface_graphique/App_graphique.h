#pragma once
#include <SFML/Graphics.hpp>
#include "../Jeu/Jeu.h"


namespace app_graphique {
    class App_graphique {
        private :
            int cellSize;
            int gridHeight;
            int gridWidth;
            sf::RenderWindow window;
            jeu::Jeu& jeu;
        public :
            App_graphique(jeu::Jeu& j, int cellSize = 10, int gridHeight = 80, int gridWidth = 80);
            ~App_graphique() = default;
            void run();
            void render(sf::RenderWindow &window);
    };
}