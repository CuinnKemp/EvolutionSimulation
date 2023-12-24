#ifndef ORGANISM
#define ORGANISM

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Organism {
    public:
        sf::Vector2f position;
        sf::Vector2f dimensions = {250,250};
        sf::CircleShape shape;
        int type = 0;
        bool isDead = false;

        Organism(){
            this->position = {(float)(rand()%250),(float)(rand()%250)};
            this->shape.setFillColor(sf::Color(255,255,255));
            this->shape.setRadius(1);
            this->shape.setPosition(position);
            
            
        }

        Organism(float x, float y){
            this->position = {x,y};
        }

        void update(){
            // get direction in degrees;
            float direction = (rand()%(314159*2))/pow(10,5);
            sf::Vector2f movementVector = {(float)0.1 * (float)cos(direction), (float)0.1 * (float)sin(direction)};
            while ((position.x + movementVector.x < 0 || position.x + movementVector.x > dimensions.x) || (position.y + movementVector.y < 0 || position.y + movementVector.y > dimensions.y)){
                direction = (rand()%(314159*2))/pow(10,5);
                movementVector = {(float)0.1 * (float)cos(direction), (float)0.1 * (float)sin(direction)};
            }
            
            position += movementVector;
            this->shape.setPosition(position);
        }
        virtual void update(list<Organism*>* organisms) {
            cout << "failed" << endl;
        }

        virtual void spawnBased(list<Organism*>* organisms){
            cout << "should not be here" << endl;
        }

        void draw(sf::RenderWindow* window){
            window->draw(this->shape);
        }



};

#endif //ORGANISM