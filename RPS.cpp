#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

#include "rock.h"
#include "paper.h"
#include "scissor.h"

int main()
{
    list<Organism*> organisms;
    for (int i = 0; i < 200; i++){
        organisms.push_back(new Rock);
        // organisms.push_back(new Prey);
    }
    for (int i = 0; i < 200; i++){
        // organisms.push_back(new Predator);
        organisms.push_back(new Paper);
    }

    for (int i = 0; i < 200; i++){
        // organisms.push_back(new Predator);
        organisms.push_back(new Scissor);
    }

    int counter = 0;
    while (counter < 2000){
        for (auto it = organisms.begin(); it != organisms.end(); it++){
            (*it)->update(&organisms);
            if ((*it)->isDead){
                it = organisms.erase(it);
            }
        }
        counter++;
    }

    sf::RenderWindow window(sf::VideoMode(Organism::dimensions[0], Organism::dimensions[1]), "Rock Paper Scissors");
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

        vector<int> types = {0,0,0};
        for (auto it = organisms.begin(); it != organisms.end(); it++){
            (*it)->update(&organisms);
            if ((*it)->isDead){
                it = organisms.erase(it);
            } else{
                (*it)->draw(&window);
                types[(*it)->type -1]++;
            }
        }

        string info =   "Rock: " + to_string(types[0]) + 
                        "\nPaper:" + to_string(types[1]) +
                        "\nScissor: " + to_string(types[2]);

        text.setString(info);
        
        window.draw(text);

        window.display();
    }
    
    return 0;
}
