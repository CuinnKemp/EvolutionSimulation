#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#include "predator.h"
#include "prey.h"

int main()
{
    bool show = true;

    sf::RenderWindow window(sf::VideoMode(Organism::dimensions[0], Organism::dimensions[1]), "Predators and Prey");
    list<Organism*> organisms;
    for (int i = 0; i < 400; i++){
        organisms.push_back(new Predator);
        // organisms.push_back(new Prey);
    }
    for (int i = 0; i < 400; i++){
        // organisms.push_back(new Predator);
        organisms.push_back(new Prey);
    }

    window.setFramerateLimit(60);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("Font.ttf");
    text.setFont(font);
    text.setCharacterSize(10);

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

        string info = "Predator: " + to_string(types[0]) + "\nPrey:" + to_string(types[1]);

        text.setString(info);
        
        window.draw(text);

        window.display();
    }
    

    return 0;
}