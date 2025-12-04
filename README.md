# Projet POO : le jeu de la vie

## Présentation du projet
Ce projet implémente une version orientée objet du jeu de la vie de Conway en C++. L'application propose plusieurs modes :

- Simulation console  
- Édition manuelle de la grille via un éditeur textuel  
- Simulation graphique via SFML  
- Lecture et écriture de grilles depuis et vers des fichiers  

Un futur fichier `main_tests.cpp` permettra l'intégration de tests unitaires pour valider le code.

## Contenu du dépôt et architecture

ProjetPOO_Groupe1/
- ├── main.cpp # point d’entrée principal (menu console et graphique)
- ├── main_tests.cpp # (à venir) Main dédié aux tests unitaires
- ├── Cellules_MVO/ # modules représentant les états des cellules (Vivante, Morte, Obstacle)
- ├── grille/ # module Grille et Case
- ├── Jeu/ # classe Jeu (gestion de la simulation, grille, règles)
- ├── Gestion_fichier/ # lecture/écriture de grilles
- ├── editeur/ # éditeur de grille en mode console
- ├── interface_graphique/ # App_graphique : interface graphique avec SFML
- └── … (autres modules si besoin)

### Principaux composants

- **Grille / Case / Cellule** : représentation de la grille, des cellules, et de leur état (vivante, morte, obstacle).  
- **Jeu** : gère la grille courante, la règle de Conway, les itérations et la stabilité.  
- **Gestion_fichier** : lecture et écriture de fichiers texte pour les grilles.  
- **Editeur** : permet de modifier manuellement la grille dans la console via un curseur et des commandes clavier.  
- **App_graphique** : affiche graphiquement la grille et simule visuellement l'évolution.  
- **main** : menu textuel permettant de choisir l’action (charger, créer, éditer, simuler, sauvegarder, afficher, interface graphique, quitter).

## Prérequis et compilation

- Compilateur C++ (C++11 ou supérieur)  
- Pour le mode graphique : SFML installée ([https://www.sfml-dev.org](https://www.sfml-dev.org))

### Exemple de compilation (Linux / g++) :

```bash
g++ -std=c++17 -I include/ -o JeuDeLaVie main.cpp ... -lsfml-graphics -lsfml-window -lsfml-system
(À adapter selon l’organisation des fichiers, Makefile ou CMake possible.)

Utilisation
Après compilation, exécuter le binaire :

Le menu principal s'affiche.

Charger une grille depuis un fichier ou créer une grille vide.

Éditer la grille manuellement si souhaité.

Simuler en console ou lancer l’interface graphique.

Sauvegarder la grille dans un fichier.

Afficher la grille dans la console.

Tests unitaires
Un nouveau fichier main_tests.cpp permettra de réaliser des tests unitaires :

Compilation et exécution des tests à prévoir

Modules testés : Grille, règles, etc.

Couverture des tests à déterminer

Contribution et roadmap
À venir :

Intégration complète des tests unitaires

Documentation plus détaillée (exemples de fichiers grille, captures d’écran interface graphique)

Amélioration du code et modularité

Système de configuration avancé et sauvegarde multiple

Pour contribuer, fork le projet, crée une branche, puis soumets une pull request.
