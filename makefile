PreyPredator: PreyPredator.cpp organism.h predator.h prey.h -lsfml-graphics -lsfml-window -lsfml-system
	g++ PreyPredator.cpp -lsfml-graphics -lsfml-window -lsfml-system -o PreyPredator

make test-PreyPredator: PreyPredator
	./PreyPredator

RPS: RPS.cpp organism.h rock.h paper.h scissor.h -lsfml-graphics -lsfml-window -lsfml-system
	g++ RPS.cpp -lsfml-graphics -lsfml-window -lsfml-system -o RPS

make test-RPS: RPS
	./RPS