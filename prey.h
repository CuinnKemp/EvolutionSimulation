#include "organism.h"
#include "predator.h"

#ifndef PREY
#define PREY
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;


class Prey : public Organism {
public:
    vector<vector<float>> weights;
    static const int layers = 3;
    int clock = 500;
    int bias;
    int kidCount = 0;
    static const short int movespeed = 3;

    // used on in(*it)ial spawns
    Prey(){
        clock += rand()%1000;
        this->position = {(float)(rand()%((int)dimensions[0])),(float)(rand()%((int)dimensions[1]))};
        this->type = 2;
        this->shape.setFillColor(sf::Color(0,0,255));
        this->shape.setRadius(1);
        this->shape.setPosition(position);

        // model creation 
        // weigths: Position of closest prey, Position of closest peer, current Position
        for (int i = 0; i < layers; i++){
            this->weights.push_back({(float)((rand()%10000 - 5000)/1000.0), (float)((rand()%10000 - 5000)/1000.0), (float)((rand()%10000 - 5000)/1000.0), (float)((rand()%10000 - 5000)/1000.0), (float)((rand()%10000 - 5000)/1000.0), (float)((rand()%10000 - 5000)/1000.0)});
        }
        this->bias = (rand()%1000 - 500)/500;
        


    } 

    // used on add(*it)ional spawns
    Prey(float x, float y, vector<vector<float>> weights, int bias){
        this->position = {x,y};
        this->type = 2;
        this->shape.setFillColor(sf::Color(0,0,255));
        this->shape.setRadius(1);
        this->shape.setPosition(position);

        // model creation
        for (int i = 0; i < weights.size(); i++){
            vector<float> temp;
            for (int j = 0; j < weights[0].size(); j++){
                temp.push_back(weights[i][j] + (rand()%200000 - 100000)/1000000.0);
            }
            this->weights.push_back(temp);
        }
        this->bias = bias + (rand()%2000 - 1000)/1000.0;
    } 

    void update(list<Organism*>* organisms) override {
        if (kidCount == 2){
            isDead = true;
        }

        if (isDead){
            return;
        }

        this->clock--;
        if (this->clock <= 0){
            clock = 500 + rand()%500;
            organisms->push_back(new Prey(position.x,position.y, weights, bias));
            kidCount++;
        }

        vector<int> variables = {INT_MAX,INT_MAX,INT_MAX,INT_MAX,(int)this->position.x,(int)this->position.y};
        vector<int> minDists = {INT_MAX, INT_MAX};
        // get new variable values;
        for (auto it = organisms->begin(); it != organisms->end(); it++){
            switch((*it)->type){
                case 1:{
                    double newDist = sqrt(pow((*it)->position.x - this->position.x,2) + pow((*it)->position.y - this->position.y,2));
                    if (newDist <= 2){
                        isDead = true;
                        (*it)->spawnBased(organisms);
                        return;
                    } else if (newDist < minDists[0]){
                        variables[2] = (*it)->position.x;
                        variables[3] = (*it)->position.y;
                        minDists[0] = newDist;
                    }
                    break;
                }

                case 2:{
                    double newDist = sqrt(pow((*it)->position.x - this->position.x,2) + pow((*it)->position.y - this->position.y,2));
                    if (newDist < minDists[1]){
                        variables[0] = (*it)->position.x;
                        variables[1] = (*it)->position.y;
                        minDists[1] = newDist;
                    }
                    break;
                }
                    

                default:
                    break;
            }
        }

        double direction = 0;
        for (int i = 0; i < weights.size(); i++){
            for (int j = 0; j < weights[0].size(); j++){
                if (variables[j] == INT_MAX){
                    continue;
                }
                direction += weights[i][j] * pow(variables[j], j+1);
            }
        }

        direction += bias;
        this->position = this->position  +  sf::Vector2f(movespeed * cos(direction), movespeed * sin(direction));
        shape.setPosition(this->position);
        if (position.x < 0){
            position.x = 0;
        } else if (position.x > dimensions[0]){
            position.x = dimensions[0];
        }
        if (position.y < 0){
            position.y = 0;
        } else if (position.y > dimensions[0]){
            position.y = dimensions[1];
        }
    }
};

#endif // PREY