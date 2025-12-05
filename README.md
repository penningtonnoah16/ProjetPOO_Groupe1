# Projet POO – Jeu de la vie (C++)

## Présentation

Ce projet implémente une version orientée objet du **Jeu de la vie** de John Conway.  
Il propose une architecture modulaire organisée autour de classes représentant :

- les cellules (vivantes, mortes, obstacles),  
- les cases,
- la grille,
- et le jeu lui-même (gestion des règles et évolution).

Le projet inclut :
- une **interface console complète**,  
- un **éditeur de grille interactif**,  
- une **interface graphique SFML**,  
- un **système de sauvegarde/chargement de grilles**,  
- des **tests unitaires intégrés** directement dans le code (pas de main séparé).

---

## Fonctionnalités

### Gestion du jeu
- Initialisation d’une grille vide ou chargée depuis fichier  
- Application automatisée des règles de Conway  
- Détection de stabilité / oscillation  
- Exécution étape par étape ou automatique  
- Affichage de la grille en console

### Éditeur de grille (mode console)
- Déplacement d’un curseur sur la grille  
- Ajout / suppression de cellules vivantes  
- Placement d’obstacles  
- Sauvegarde directe depuis l’éditeur  
- Visualisation instantanée des modifications

### Système de fichiers
- Chargement d’une grille depuis fichier texte  
- Sauvegarde d’une grille existante  
- Validation du format des fichiers  
- Gestion d’erreurs (format incorrect, taille invalide, etc.)

### Tests unitaires intégrés
Les tests unitaires sont **directement intégrés au code** pour vérifier :
- la création de la grille,  
- l’évolution correcte des cellules,  
- la gestion des obstacles,  
- les règles du jeu,  
- la lecture/écriture des fichiers.

### Interface graphique (SFML)
- Représentation visuelle de la grille  
- Bouton “Suivant” / “Lancer la simulation”  
- Animation fluide des itérations  
- Affichage des cellules vivantes, mortes et obstacles  
- Interaction utilisateur : choix de mode / exit graphique

### Menu principal (console)
Depuis `main.cpp`, l’utilisateur peut :
- créer une nouvelle grille  
- charger une grille depuis fichier  
- éditer une grille  
- lancer la simulation (console)  
- lancer la simulation (graphique SFML)  
- sauvegarder  
- quitter  

---

## Structure du projet

ProjetPOO_Groupe1/
- ├── Cellules_MVO/ # états des cellules : Morte, Vivante, Obstacle
- ├── Grille/ # classes Grille et Case
- ├── Jeu/ # logique du jeu et règles
- ├── Gestion_fichier/ # lecture/écriture de fichiers .txt
- ├── editeur/ # éditeur de grille en mode console
- ├── interface_graphique/ # interface avec SFML
- ├── test_unitaires/ # tests intégrés aux différents modules
- ├── main.cpp # point d’entrée du programme
- ├── Makefile # compilation automatique
- └── README.md # documentation

---

## Compilation & exécution

Le projet inclut un **Makefile**, donc aucune commande manuelle compliquée n’est nécessaire.

### Compiler
```bash
make
```
### Lancer le programme
```bash
./main
```

## Auteurs

Projet réalisé par :
Blandeau Adrien
Pennington Noah
CPI A2 INFO — 2025/2026
