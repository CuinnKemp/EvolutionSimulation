simulation: main.cpp organism.h predator.h prey.h -lsfml-graphics -lsfml-window -lsfml-system
	g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o simulation

make test: simulation
	./simulation