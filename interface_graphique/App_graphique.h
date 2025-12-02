namespace app_graphique {
    class App_graphique{
        private : 
            sf::RenderWindow window;
            int gridHeight;
            int gridWidth;
            int cellSize;
            Jeu& jeu;
        public :
            void run();
            void render(sf::RenderWindow);
    }
}