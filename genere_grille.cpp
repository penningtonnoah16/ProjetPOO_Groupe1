#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::ofstream f("test_graphique");
    
    const int lignes = 50;
    const int colonnes = 50;
    
    // Écrire les dimensions de la grille en première ligne
    f << lignes << " " << colonnes << "\n";
    
    std::srand(std::time(nullptr));
    
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            f << (std::rand() % 3); // 0, 1 ou 2
            if (j != colonnes - 1) f << " ";
        }
        f << "\n";
    }
    
    f.close();
    return 0;
}
