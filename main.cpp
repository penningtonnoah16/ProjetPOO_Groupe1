#include <iostream>

#include "Case/Case.h"

#include "Cellules_MVO/Cellule.h"
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"
#include "Cellules_MVO/Obstacle.h"

int main() {

    using namespace cases;
    using namespace cellules;

    Cellule* c1 = new Vivant();
    std::cout << "c1 est vivante ? " << c1->estVivante() << std::endl;

    Cellule* c2 = new Mort();
    std::cout << "c2 est vivante ? " << c2->estVivante() << std::endl;

    Cellule* c3 = new Obstacle();
    std::cout << "c3 est vivante ? " << c3->estVivante() << std::endl;

    Case maCase(2, 3, c1);
    std::cout << "Case coords = (" << maCase.getX()
            << "," << maCase.getY() << ")" << std::endl;

    std::cout << "La cellule dans maCase est vivante ? "
              << maCase.getEtat()->estVivante() << std::endl;

    return 0;
}
