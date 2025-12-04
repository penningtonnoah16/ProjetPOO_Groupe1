#pragma once
#include <SFML/Graphics.hpp>
#include "../Jeu/Jeu.h"

namespace app_graphique {
    class App_graphique {

        private:
            int cellSize;
            jeu::Jeu& jeu;
            sf::RenderWindow window;
            int delaiMs;

        public:
            App_graphique(jeu::Jeu& j, int cell);

            void setDelai(int ms) { delaiMs = ms; }
            void render();
            void run(int iterations);
    };
}
