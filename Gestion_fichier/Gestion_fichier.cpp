#include "Gestion_fichier.h"
#include "../Grille/Grille.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"
#include <fstream> // Pour les opérations de fichier
#include <filesystem> // Pour la gestion des chemins de fichiers
#include <iostream>
#include <string>

namespace gestion_fichier {

    void GestionFichier::ecrireGrille(const grille::Grille& grille, const std::string& chemin, int numero) { // Écrire la grille dans un fichier

    std::filesystem::path p(chemin); // Convertir le chemin en objet path

    std::filesystem::path filePath; // Chemin final du fichier

    if (std::filesystem::is_directory(p)) { // Si c'est un dossier, créer un nom de fichier avec numéro

        filePath = p / (p.parent_path().stem().string() + std::to_string(numero) + ".txt");
    }
    else { // Sinon, utiliser le chemin donné

        filePath = p;
    }

    std::ofstream fichier(filePath); // Ouvrir le fichier en écriture

    if (!fichier.is_open()) {

        std::cerr << "Erreur d'ouverture : " << filePath << "\n";
        return;
    }

    int lignes = grille.getLignes();
    int colonnes = grille.getColonnes();

    fichier << lignes << " " << colonnes << "\n"; // Écrire dimensions

    for (int i = 0; i < lignes; ++i) { // Parcourir les lignes
        for (int j = 0; j < colonnes; ++j) { // Parcourir les colonnes

            fichier << ( // Écrire l'état de chaque cellule
                dynamic_cast<cellules::Vivant*>(grille.getCase(i, j)->getEtat()) ? 1 : // Cellule vivante
                dynamic_cast<cellules::Obstacle*>(grille.getCase(i, j)->getEtat()) ? 2 : 0 // Cellule obstacle ou morte
            );
            if (j < colonnes - 1) fichier << " "; // Espacement entre les cellules
        }
        fichier << "\n";
    }
}

    std::string GestionFichier::creerDossierSortie(const std::string& fichier){ // Créer un dossier de sortie basé sur le nom du fichier

        std::filesystem::path p(fichier); // Convertir le chemin en objet path
        std::string nomSansExtension = p.stem().string(); // Obtenir le nom sans extension
        std::string dossier = nomSansExtension + "_out"; // Nom du dossier de sortie

        if (!std::filesystem::exists(dossier)) { // Créer le dossier s'il n'existe pas
            std::filesystem::create_directory(dossier);
        }

        return dossier;
}

    grille::Grille* GestionFichier::lireGrille(const std::string& chemin) { // Lire une grille depuis un fichier

        std::ifstream fichier(chemin); // Ouvrir le fichier en lecture

        if (!fichier.is_open()) {

            std::cerr << "Erreur lors de l'ouverture du fichier pour lecture: " << chemin << std::endl;
            return nullptr;
        }

        int lignes, colonnes;
        fichier >> lignes >> colonnes;

        grille::Grille* grille = new grille::Grille(lignes, colonnes); // Créer une nouvelle grille

        for (int i = 0; i < lignes; ++i) { // Parcourir les lignes
            for (int j = 0; j < colonnes; ++j) { // Parcourir les colonnes

                int valeur;
                fichier >> valeur; // Lire l'état de la cellule
                if (valeur == 1){ // Cellule vivante

                    grille->getCase(i, j)->setEtat(new cellules::Vivant()); // Définir l'état de la cellule
                }
                else if (valeur == 2){ // Cellule obstacle

                    grille->getCase(i, j)->setEtat(new cellules::Obstacle());
                }
                else { // Cellule morte
                    
                    grille->getCase(i, j)->setEtat(new cellules::Mort());
                }
            }
        }

        fichier.close(); // Fermer le fichier
        return grille;
    }
}