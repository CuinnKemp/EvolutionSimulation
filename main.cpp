#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#include "organism.h"
#include "predator.h"
#include "prey.h"

int main()
{
    bool show = true;

    sf::RenderWindow window(sf::VideoMode(250, 250), "Predators and Prey");
    list<Organism*> organisms;
    for (int i = 0; i < 35; i++){
        organisms.push_back(new Predator);
        // organisms.push_back(new Prey);
    }
    for (int i = 0; i < 300; i++){
        // organisms.push_back(new Predator);
        organisms.push_back(new Prey);
    }

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        vector<int> types = {0,0};
        for (auto it = organisms.begin(); it != organisms.end(); it++){
            (*it)->update(&organisms);
            if ((*it)->isDead){
                it = organisms.erase(it);
            } else{
                (*it)->draw(&window);
                types[(*it)->type -1]++;
            }
        }

        window.display();
    }
    

    return 0;
}