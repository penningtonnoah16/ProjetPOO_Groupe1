namespace app_graphique {
    class App_graphique {
        private :
            sf::renderWindow window;
            int cellSize;
            int gridHeight;
            int gridWidth;
            Jeu& jeu;
        public :
            App_graphique() = default();
            ~App_graphique();
            void run();
            void render();
    }
}