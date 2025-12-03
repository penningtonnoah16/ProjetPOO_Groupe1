# ========================
# Makefile pour projet SFML
# ========================

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -Wall \
           -I./interface_graphique \
           -I./Jeu \
           -I./Grille \
           -I./Case \
           -I./GestionFichier \
           -I./Regles \
           -I./Cellules

# Bibliothèques pour le linkage SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Fichiers sources
SRCS = test_app_graphique.cpp \
       interface_graphique/App_graphique.cpp \
       Jeu/Jeu.cpp \
       Grille/Grille.cpp \
       Case/Case.cpp \
       Gestion_fichier/Gestion_fichier.cpp \
       Regles/Conway.cpp \
       Cellules_MVO/Mort.cpp \
       Cellules_MVO/Vivant.cpp \
       Cellules_MVO/Obstacle.cpp

# Fichiers objets correspondants
OBJS = $(SRCS:.cpp=.o)

# Nom de l'exécutable
TARGET = test_app

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et exécutable
clean:
	rm -f $(OBJS) $(TARGET)

