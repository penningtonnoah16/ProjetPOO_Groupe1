all: main

CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror
LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o main main-debug
