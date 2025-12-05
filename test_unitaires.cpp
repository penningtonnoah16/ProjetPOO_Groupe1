#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>


#include "Jeu/Jeu.h" 
#include "Grille/Grille.h" 
#include "Cellules_MVO/Vivant.h"
#include "Cellules_MVO/Mort.h"
#include "Cellules_MVO/Obstacle.h"

namespace fs = std::filesystem;
using namespace jeu;
using namespace grille;
using namespace cellules;

// Compteurs de tests
int testsPasses = 0;
int testsEchoues = 0;

// Macro d'assertion simple
#define CHECK(condition, message) \
    if (condition) { \
        std::cout << "[PASS] " << message << std::endl; \
        testsPasses++; \
    } else { \
        std::cerr << "[FAIL] " << message << " (Condition échouée à la ligne " << __LINE__ << ")" << std::endl; \
        testsEchoues++; \
    }

// Simule la création d'une Grille à partir d'un vecteur d'états
// 0: Mort, 1: Vivant, 2: Obstacle
Grille* creerGrilleManuelle(int L, int C, const std::vector<int>& etats) {
    if (etats.size() != L * C) {
        throw std::invalid_argument("La taille du vecteur d'états ne correspond pas à la taille de la grille.");
    }
    return new Grille(L, C, etats);
}

// Fonction utilitaire pour vérifier l'état d'une case
int getEtatCase(const Grille* g, int x, int y) {
    if (dynamic_cast<Obstacle*>(g->getCase(x, y)->getEtat())) return 2;
    if (g->estVivante(x, y)) return 1;
    return 0;
}

// Fonction pour afficher le titre d'une suite de tests
void printTestSuiteTitle(const std::string& title) {
    std::cout << "\n========================================================" << std::endl;
    std::cout << "SUITE DE TESTS : " << title << std::endl;
    std::cout << "========================================================" << std::endl;
}

// ======================================================================================
// TESTS DE LA CLASSE GRILLE
// ======================================================================================

void testGrilleInitialisation() {
    Grille g(3, 3);
    CHECK(g.getLignes() == 3, "Grille Init: Vérification des lignes.");
    CHECK(g.getColonnes() == 3, "Grille Init: Vérification des colonnes.");

    bool toutesMortes = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (getEtatCase(&g, i, j) != 0) {
                toutesMortes = false;
                break;
            }
        }
    }
    CHECK(toutesMortes, "Grille Init: Toutes les cellules sont Mortes.");
}

void testGrilleVoisinsSimples() {
    // [1 0 0]
    // [0 X 0] -> X a 1 voisin
    // [0 0 0]
    std::vector<int> etats = {1, 0, 0, 0, 0, 0, 0, 0, 0};
    Grille* g = creerGrilleManuelle(3, 3, etats);
    
    CHECK(g->compterVoisinsVivants(1, 1) == 1, "Voisins Simples: Centre a 1 voisin.");
    CHECK(g->compterVoisinsVivants(0, 0) == 0, "Voisins Simples: Coin a 0 voisin.");

    delete g;
}

void testGrilleVoisinsToriques() {
    // [0 0 1]
    // [0 X 0] 
    // [1 0 1]
    std::vector<int> etats = {0, 0, 1, 0, 0, 0, 1, 0, 1};
    Grille* g = creerGrilleManuelle(3, 3, etats);

    // Position X (1, 1) a 3 voisins directs: (0, 2), (2, 0), (2, 2)
    CHECK(g->compterVoisinsVivants(1, 1) == 3, "Voisins Toriques: Centre a 3 voisins.");

    // Position (0, 0) (coin) a 3 voisins vivants: (0, 2), (2, 0), (2, 2)
    CHECK(g->compterVoisinsVivants(0, 0) == 3, "Voisins Toriques: Coin (0,0) a 3 voisins toriques.");

    delete g;
}

void runGrilleTests() {
    printTestSuiteTitle("Grille");
    testGrilleInitialisation();
    testGrilleVoisinsSimples();
    testGrilleVoisinsToriques();
}

// ======================================================================================
// TESTS DE LA CLASSE JEU (Logique de Conway)
// ======================================================================================

void testConwaySurpopulation() {
    // [1 1 1]
    // [1 X 1] -> X (1,1) a 8 voisins vivants. Doit mourir.
    // [1 1 1]
    std::vector<int> etats = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Jeu jeu_test("");
    jeu_test.setGrille(creerGrilleManuelle(3, 3, etats));
    
    jeu_test.iterer();

    CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 0, "Règle Surpopulation: Cellule centre doit mourir."); 
    CHECK(getEtatCase(jeu_test.getGrille(), 0, 0) == 0, "Règle Surpopulation: Cellule coin doit mourir."); 
}

void testConwaySolitude() {
    // [0 0 0]
    // [0 X 1] -> X (1,1) est Vivante. Elle a 1 voisin vivant. Doit mourir.
    // [0 0 0]
    std::vector<int> etats = {0, 0, 0, 0, 1, 1, 0, 0, 0};
    Jeu jeu_test("");
    jeu_test.setGrille(creerGrilleManuelle(3, 3, etats));
    
    jeu_test.iterer();

    CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 0, "Règle Solitude: Cellule doit mourir avec 1 voisin."); 
}

void testConwayNaissance() {
    // [1 1 0]
    // [1 M 0] -> M (1,1) est Morte. Elle a 3 voisins. Doit naître.
    // [0 0 0]
    std::vector<int> etats = {1, 1, 0, 1, 0, 0, 0, 0, 0};
    Jeu jeu_test("");
    jeu_test.setGrille(creerGrilleManuelle(3, 3, etats));
    
    jeu_test.iterer();

    CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 1, "Règle Naissance: Cellule Morte doit naître avec 3 voisins."); 
}

void testConwayStabilitéBloc() {
    // Le "Bloc" : figure stable qui ne change pas.
    std::vector<int> etats = {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };
    Jeu jeu_test("");
    jeu_test.setGrille(creerGrilleManuelle(4, 4, etats));
    
    jeu_test.iterer();

    CHECK(jeu_test.estStable() == true, "Règle Stabilité: Le Bloc est stable."); 
    CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 1, "Règle Stabilité: Cellule (1,1) est toujours vivante."); 
}

void runConwayTests() {
    printTestSuiteTitle("Jeu - Logique de Conway");
    testConwaySurpopulation();
    testConwaySolitude();
    testConwayNaissance();
    testConwayStabilitéBloc();
}

// ======================================================================================
// TESTS DE LA CLASSE JEU (Fonctionnalités)
// ======================================================================================

void testJeuEstStable() {
    // Test de Stabilité (Stable)
    std::vector<int> etatsStable = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
    Jeu jeu_test_stable("");
    jeu_test_stable.setGrille(creerGrilleManuelle(4, 4, etatsStable));
    
    jeu_test_stable.iterer();
    CHECK(jeu_test_stable.estStable() == true, "Fonctionnalité Stabilité: Le bloc stable est détecté comme stable.");
    
    // Test de Stabilité (Non Stable - Clignotant)
    // [0 0 0] -> [0 1 0]
    // [1 1 1] -> [0 1 0]
    // [0 0 0] -> [0 1 0]
    std::vector<int> etatsOscillant = {0, 0, 0, 1, 1, 1, 0, 0, 0};
    Jeu jeu_test_oscillant("");
    jeu_test_oscillant.setGrille(creerGrilleManuelle(3, 3, etatsOscillant));
    
    jeu_test_oscillant.iterer(); // Changement
    CHECK(jeu_test_oscillant.estStable() == false, "Fonctionnalité Stabilité: L'oscillateur est détecté comme non stable (Itération 1).");
    
    jeu_test_oscillant.iterer(); // Changement à nouveau
    CHECK(jeu_test_oscillant.estStable() == false, "Fonctionnalité Stabilité: L'oscillateur est détecté comme non stable (Itération 2).");
}

void runFonctionnalitesTests() {
    printTestSuiteTitle("Jeu - Fonctionnalités");
    testJeuEstStable();
    // Le test de chargement est DÉPENDANT des fonctions réelles de GestionFichier (lireGrille).
    // Il est laissé commenté.
    /*
    testJeuChargement();
    */
}

// ======================================================================================
// FONCTION PRINCIPALE POUR L'EXÉCUTION DES TESTS
// ======================================================================================

int lancerTestsUnitaires() {
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "DEBUT DE L'EXECUTION DES TESTS UNITAIRES (C++ Standard)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    try {
        runGrilleTests();
        runConwayTests();
        runFonctionnalitesTests();
    } catch (const std::exception& e) {
        std::cerr << "\nERREUR CRITIQUE PENDANT L'EXECUTION DES TESTS: " << e.what() << std::endl;
        testsEchoues++;
    } catch (...) {
        std::cerr << "\nERREUR CRITIQUE INCONNUE PENDANT L'EXECUTION DES TESTS." << std::endl;
        testsEchoues++;
    }

    std::cout << "\n--------------------------------------------------------" << std::endl;
    std::cout << "RESUME DES TESTS" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Total des tests exécutés: " << (testsPasses + testsEchoues) << std::endl;
    std::cout << "Tests réussis: " << testsPasses << std::endl;
    std::cout << "Tests échoués: " << testsEchoues << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    return testsEchoues > 0 ? 1 : 0;
}