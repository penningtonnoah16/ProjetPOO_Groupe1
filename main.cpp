#include <iostream>
#include "Case/Case.h"
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"
#include "Cellules_MVO/Obstacle.h"
#include "Grille/Grille.h"
#include "Gestion_fichier/Gestion_fichier.h"

int main() {

    std::cout << "TEST : CELLULES (Vivant / Mort / Obstacle)\n";

    cellules::Cellule* v = new cellules::Vivant();
    cellules::Cellule* m = new cellules::Mort();
    cellules::Cellule* o = new cellules::Obstacle();

    std::cout << "Vivant estVivante = " << v->estVivante() << "\n";
    std::cout << "Mort estVivante   = " << m->estVivante() << "\n";
    std::cout << "Obstacle estVivante = " << o->estVivante() << "\n";



    std::cout << "\n TEST : CASE\n";

    cases::Case c(2, 3, v);
    std::cout << "Case(2,3) -> estVivante = " 
              << c.getEtat()->estVivante() << "\n";

    c.setEtat(new cellules::Mort());
    std::cout << "Après setEtat(Mort) : " 
              << c.getEtat()->estVivante() << "\n";



    std::cout << "\nTEST 3 : GRILLE 5x5\n";

    grille::Grille g(5, 5);

    std::cout << "Cellule (2,3) vivante ? " 
              << g.estVivante(2,3) << "\n";   // devrait être 0

    g.getCase(2,3)->setEtat(new cellules::Vivant());
    std::cout << "Après setEtat(2,3,Vivant) -> " 
              << g.estVivante(2,3) << "\n";   // devrait être 1

    std::cout << "Voisins vivants de (2,3) : " 
              << g.compterVoisinsVivants(2,3) << "\n";  // 0

    g.getCase(2,2)->setEtat(new cellules::Vivant());
    g.getCase(2,4)->setEtat(new cellules::Vivant());
    g.getCase(1,3)->setEtat(new cellules::Vivant());

    std::cout << "Voisins vivants après activation de 3 cases : "
              << g.compterVoisinsVivants(2,3) << "\n";  // devrait être 3



    std::cout << "\nTEST : ECRITURE FICHIER\n";

    std::string dossier = "test_out";
    gestion_fichier::GestionFichier::creerDossierSortie(dossier);

    gestion_fichier::GestionFichier::ecrireGrille(g, dossier, 0);

    std::cout << "Grille écrite dans test_out/grille_0.txt\n";



    std::cout << "\nTEST : LECTURE FICHIER\n";

    grille::Grille* g2 = gestion_fichier::GestionFichier::lireGrille(dossier + "/grille_0.txt");

    std::cout << "Cellule (2,3) lue -> " 
              << g2->estVivante(2,3) << "\n";

    std::cout << "Cellule (1,3) lue -> " 
              << g2->estVivante(1,3) << "\n";


    delete g2;

    return 0;
}
