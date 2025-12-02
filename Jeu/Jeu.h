#include <string>

namespace jeu {
    class Jeu {
        public :
            Grille grille;
            Règle* regle;
            std::string cheminFichierEntree;
            bool stable;
        private :
            void charger(std::string);
            void iterer()
            bool estStable();
            void executerConsole(int);
            const Grille& get_Grille();
    }
}