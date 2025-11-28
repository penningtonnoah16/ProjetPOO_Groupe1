#include <iostream>
#include "Grille/Grille.h"
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"

int main() {
    grille::Grille g(5, 5);

    std::cout << "Etat initial de (2,3) : " << g.estVivante(2, 3) << std::endl;

    g.getCase(2, 3)->setEtat(new cellules::Vivant());
    std::cout << "Etat de (2,3) après passage en vivant : " << g.estVivante(2, 3) << std::endl;

    std::cout << "Nombre de voisins vivants autour de (2,3) : " 
              << g.compterVoisinsVivants(2, 3) << std::endl;

    g.getCase(2, 2)->setEtat(new cellules::Vivant());
    g.getCase(2, 4)->setEtat(new cellules::Vivant());
    g.getCase(1, 3)->setEtat(new cellules::Vivant());

    std::cout << "Nombre de voisins vivants après activation de 3 cellules : " 
              << g.compterVoisinsVivants(2, 3) << std::endl;

    return 0;
}
