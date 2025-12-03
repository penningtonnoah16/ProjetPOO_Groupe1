#include "Gestion_fichier.h"
#include "../Grille/Grille.h"
#include "../Cellules_MVO/Vivant.h"
#include "../Cellules_MVO/Mort.h"
#include "../Cellules_MVO/Obstacle.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

namespace gestion_fichier {

    void GestionFichier::ecrireGrille(const grille::Grille& grille, const std::string& chemin, int numero) {

    std::filesystem::path p(chemin);

    std::filesystem::path filePath;

    if (std::filesystem::is_directory(p)) {

        filePath = p / (p.parent_path().stem().string() + std::to_string(numero) + ".txt");
    }
    else {

        filePath = p;
    }

    std::ofstream fichier(filePath);

    if (!fichier.is_open()) {

        std::cerr << "Erreur d'ouverture : " << filePath << "\n";
        return;
    }

    int lignes = grille.getLignes();
    int colonnes = grille.getColonnes();

    fichier << lignes << " " << colonnes << "\n";

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {

            fichier << (
                dynamic_cast<cellules::Vivant*>(grille.getCase(i, j)->getEtat()) ? 1 :
                dynamic_cast<cellules::Obstacle*>(grille.getCase(i, j)->getEtat()) ? 2 : 0
            );
            if (j < colonnes - 1) fichier << " ";
        }
        fichier << "\n";
    }
}

    std::string GestionFichier::creerDossierSortie(const std::string& fichier){

        std::filesystem::path p(fichier);
        std::string nomSansExtension = p.stem().string();
        std::string dossier = nomSansExtension + "_out";

        if (!std::filesystem::exists(dossier)) {
            std::filesystem::create_directory(dossier);
        }

        return dossier;
}

    grille::Grille* GestionFichier::lireGrille(const std::string& chemin) {

        std::ifstream fichier(chemin);

        if (!fichier.is_open()) {

            std::cerr << "Erreur lors de l'ouverture du fichier pour lecture: " << chemin << std::endl;
            return nullptr;
        }

        int lignes, colonnes;
        fichier >> lignes >> colonnes;

        grille::Grille* grille = new grille::Grille(lignes, colonnes);

        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {

                int valeur;
                fichier >> valeur;
                if (valeur == 1){

                    grille->getCase(i, j)->setEtat(new cellules::Vivant());
                }
                else if (valeur == 2){

                    grille->getCase(i, j)->setEtat(new cellules::Obstacle());
                }
                else {
                    
                    grille->getCase(i, j)->setEtat(new cellules::Mort());
                }
            }
        }

        fichier.close();
        return grille;
    }
}