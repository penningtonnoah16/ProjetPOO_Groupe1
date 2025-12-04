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
            App_graphique(jeu::Jeu&, int);

            void setDelai(int);
            void render();
            void run(int);
    };
}
