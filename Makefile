CXX = g++
CXXFLAGS = -std=c++17 -Wall \
           -I./interface_graphique \
           -I./Jeu \
           -I./Grille \
           -I./Case \
           -I./Gestion_fichier \
           -I./Regles \
           -I./Cellules_MVO

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp \
       interface_graphique/App_graphique.cpp \
       Jeu/Jeu.cpp \
       Grille/Grille.cpp \
       Case/Case.cpp \
       Gestion_fichier/Gestion_fichier.cpp \
       Regles/Conway.cpp \
       Cellules_MVO/Mort.cpp \
       Cellules_MVO/Vivant.cpp \
       Cellules_MVO/Obstacle.cpp \
       editeur/editeur.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
