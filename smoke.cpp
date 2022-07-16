#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const float DEG_TO_RAD =  M_PI/180;

class Smoke {

    struct Particle {

        // some constants for easy editon in the future
        const float airFriction = 0.03;
        const float upwardForce = 0;
        const float angularFriction = 0.03;
        const int angleRandomness = 45; // max deviation in each direction. [degrees] 
        const int sizeRandomness = 50; // +- max deviation in size. [percentage]
        const int speedRandomness = 30; // +- max deviation in speed. [percentage]

        sf::Vector2f pos; // position
        sf::Vector2f vel; // velocity
        sf::Vector2f scale;
        
        float lifetime;
        float wVel; // angular velocity
        float rotation;

        Particle (
                    sf::Vector2f startPos,
                    float speed,
                    float angle,
                    float size,
                    float dTime = 0.f // for more continous movement (not nececery)
            ) {

            // randomise input
            speed = (1+(rand()%(2*speedRandomness)-speedRandomness)/100)*speed;
            angle = angle + rand()%(2*angleRandomness)-angleRandomness;
            size  = (1+(+rand()%(2*sizeRandomness)-sizeRandomness)/100)*size;

            // rest of setting up
            this-> pos = startPos;

            this->vel = {
                -cos(angle*DEG_TO_RAD)*speed,
                sin(angle*DEG_TO_RAD)*speed
            };

            this->scale = {
                size,
                size
            };

            this->rotation = rand()%36000/100.f;

            this-> wVel = rand()/36000/100.f-180.f;

            this->lifetime = 0.f;

            this->update(rand()%(int)(dTime*100)/100.f);
        }

        void update (
            float dTime
            ) {
                lifetime += dTime;
                // apply forces
                vel = vel * (1-airFriction*dTime);
                vel.y -= upwardForce;
                wVel = wVel * (1-angularFriction*dTime);

                //apply velocities

                pos = pos + dTime * vel;
                rotation = rotation + dTime * wVel;
        }

    };

public:

    Smoke (

        ) {
        
    }

};