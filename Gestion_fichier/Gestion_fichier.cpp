#include "Gestion_fichier.h"
#include "../Grille/Grille.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

namespace gestion_fichier {

    void GestionFichier::ecrireGrille(const grille::Grille& grille, const std::string& chemin, int numero) {
        std::ofstream fichier(chemin + "/grille_" + std::to_string(numero) + ".txt");
        if (!fichier.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier pour écriture: " << chemin << std::endl;
            return;
        }

        int lignes = grille.getLignes();
        int colonnes = grille.getColonnes();

        fichier << lignes << " " << colonnes << std::endl;

        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                fichier << (grille.getCase(i, j)->getEtat()->estVivante() ? 1 : 0);
                if (j < colonnes - 1) {
                    fichier << " ";
                }
            }
            fichier << std::endl;
        }

        fichier.close();
    }
    std::string GestionFichier::creerDossierSortie(const std::string& nomDossier) {
        std::filesystem::path chemin(nomDossier);
        if (!std::filesystem::exists(chemin)) {
            if (!std::filesystem::create_directory(chemin)) {
                std::cerr << "Erreur lors de la création du dossier: " << nomDossier << std::endl;
            }
        }
        return chemin.string();
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
                if (valeur == 1)
                    grille->getCase(i, j)->setEtat(new cellules::Vivant());
                else
                    grille->getCase(i, j)->setEtat(new cellules::Mort());

            }
        }

        fichier.close();
        return grille;
    }
}