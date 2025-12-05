#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "test_unitaires.h"
#include "../Jeu/Jeu.h" 
#include "../Grille/Grille.h" 
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"

namespace fs = std::filesystem;
using namespace jeu; 
using namespace grille;
using namespace cellules;

namespace {

    int testsPasses = 0; // Compteur de tests réussis
    int testsEchoues = 0; // Compteur de tests échoués

    // Macro pour vérifier les conditions dans les tests
    #define CHECK(condition, message) \
        if (condition) { \
            std::cout << "[PASS] " << message << std::endl; \
            testsPasses++; \
        } else { \
            std::cerr << "[FAIL] " << message << " (Condition échouée à la ligne " << __LINE__ << ")" << std::endl; \
            testsEchoues++; \
        }

        // Fonction utilitaire pour créer une grille manuellement
    Grille* creerGrilleManuelle(int L, int C, const std::vector<int>& etats) {
        if (etats.size() != static_cast<size_t>(L * C)) { // Vérification de la taille
            throw std::invalid_argument("La taille du vecteur d'états ne correspond pas à la taille de la grille.");
        }
        return new Grille(L, C, etats);
    }

    // Fonction utilitaire pour obtenir l'état d'une cellule sous forme d'entier
    int getEtatCase(const Grille* g, int x, int y) {
        if (dynamic_cast<Obstacle*>(g->getCase(x, y)->getEtat())) return 2;
        if (g->estVivante(x, y)) return 1;
        return 0;
    }

    // Tests pour la classe Grille
    void testGrilleInitialisation() {
        Grille g(3, 3);
        CHECK(g.getLignes() == 3, "Grille Init: Vérification des lignes.");
        CHECK(g.getColonnes() == 3, "Grille Init: Vérification des colonnes.");

        // Vérification que toutes les cellules sont mortes
        bool toutesMortes = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (getEtatCase(&g, i, j) != 0) {
                    toutesMortes = false;
                    break;
                }
            }
        }
        CHECK(toutesMortes, "Grille Init: Toutes les cellules sont Mortes."); // Toutes les cellules doivent être mortes
    }

    void testGrilleVoisinsSimples() { // Tests de comptage des voisins dans des cas simples
        std::vector<int> etats = {1, 0, 0, 0, 0, 0, 0, 0, 0};
        Grille* g = creerGrilleManuelle(3, 3, etats);

        CHECK(g->compterVoisinsVivants(1, 1) == 1, "Voisins Simples: Centre a 1 voisin.");
        CHECK(g->compterVoisinsVivants(0, 0) == 0, "Voisins Simples: Coin a 0 voisin.");

        delete g;
    }

    void runGrilleTests() { // Exécuter tous les tests de la classe Grille
        testGrilleInitialisation();
        testGrilleVoisinsSimples();
    }

    void testConwaySolitude() { // Test de la règle de solitude
        std::vector<int> etats = {0, 0, 0, 0, 1, 1, 0, 0, 0};
        Jeu jeu_test("");
        jeu_test.setGrille(creerGrilleManuelle(3, 3, etats)); // Cellule vivante au centre avec 1 voisin

        jeu_test.iterer();
        CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 0, "Règle Solitude: Cellule doit mourir avec 1 voisin."); 
    }

    void testConwayNaissance() { // Test de la règle de naissance
        std::vector<int> etats = {1, 1, 0, 1, 0, 0, 0, 0, 0};
        Jeu jeu_test("");
        jeu_test.setGrille(creerGrilleManuelle(3, 3, etats));

        jeu_test.iterer();
        CHECK(getEtatCase(jeu_test.getGrille(), 1, 1) == 1, "Règle Naissance: Cellule Morte doit naître avec 3 voisins."); 
    }

    void testConwayStabilitéBloc() { // Test de la règle de stabilité avec un bloc 2x2
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

    void runConwayTests() { // Exécuter tous les tests des règles de Conway
        testConwaySolitude();
        testConwayNaissance();
        testConwayStabilitéBloc();
    }

    void testJeuEstStable() { // Tests pour la fonctionnalité estStable()
        std::vector<int> etatsStable = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
        Jeu jeu_test_stable("");
        jeu_test_stable.setGrille(creerGrilleManuelle(4, 4, etatsStable));
        jeu_test_stable.iterer();
        CHECK(jeu_test_stable.estStable() == true, "Fonctionnalité Stabilité: Le bloc stable est détecté comme stable.");

        std::vector<int> etatsOscillant = {0, 0, 0, 1, 1, 1, 0, 0, 0};
        Jeu jeu_test_oscillant("");
        jeu_test_oscillant.setGrille(creerGrilleManuelle(3, 3, etatsOscillant));
        jeu_test_oscillant.iterer();
        CHECK(jeu_test_oscillant.estStable() == false, "Fonctionnalité Stabilité: L'oscillateur est détecté comme non stable (Itération 1).");
        jeu_test_oscillant.iterer();
        CHECK(jeu_test_oscillant.estStable() == false, "Fonctionnalité Stabilité: L'oscillateur est détecté comme non stable (Itération 2).");
    }

    void runFonctionnalitesTests() { // Exécuter tous les tests des fonctionnalités supplémentaires
        testJeuEstStable();
    }

}

int lancerTestsUnitaires() { // Fonction principale pour lancer tous les tests unitaires

    try { // Exécuter tous les groupes de tests
        runGrilleTests();
        runConwayTests();
        runFonctionnalitesTests();
    } catch (const std::exception& e) { // Gérer les exceptions critiques
        std::cerr << "\nERREUR CRITIQUE PENDANT L'EXECUTION DES TESTS: " << e.what() << std::endl; // Afficher le message d'erreur
    } catch (...) { // Gérer les exceptions inconnues
        std::cerr << "\nERREUR CRITIQUE INCONNUE PENDANT L'EXECUTION DES TESTS." << std::endl;
    }

    std::cout << "RESUME DES TESTS" << std::endl;
    std::cout << "Total des tests exécutés: " << (testsPasses + testsEchoues) << std::endl;
    std::cout << "Tests réussis: " << testsPasses << std::endl;
    std::cout << "Tests échoués: " << testsEchoues << std::endl;

    return testsEchoues > 0 ? 1 : 0; // Retourner 1 si des tests ont échoué, sinon 0
}
