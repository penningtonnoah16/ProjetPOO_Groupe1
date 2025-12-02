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
                fichier << grille.getCellule(i, j);
                if (j < colonnes - 1) {
                    fichier << " ";
                }
            }
            fichier << std::endl;
        }

        fichier.close();
    }