#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "smoke.cpp"

class Sprayer : public sf::Drawable {

    sf::Vector2f pos; // center of mass
    sf::Vector2f tip; // place where the smoke is commit from
    sf::Vector2f prevTip;
    float rot; // rotation
    float prevPower;
    float powerChangeSpeed;
    float angularVelocity;
    float prevRot;

    

    Smoke smoke;

    public:

    Sprayer () : pos({0,0}), rot(0), prevRot(0) { }
    Sprayer (sf::Vector2f position, float rotation) : pos(position), rot(rotation), prevRot(rotation) {
            tip.x = pos.x+cos((rot-90)*DEG_TO_RAD)*30;
            tip.y = pos.y+sin((rot-90)*DEG_TO_RAD)*30;
            this->powerChangeSpeed = 0;
            this->angularVelocity = 0;
    }

    void update (
        float dTime, 
        float desiredPower,
        float desiredRotation, 
        sf::Vector2f position
        ) {
            pos = position;

            prevRot = rot;

            powerChangeSpeed += (desiredPower-prevPower)*dTime;
            powerChangeSpeed *= 1-0.9*dTime;
            prevPower = desiredPower;

            angularVelocity += (desiredRotation-prevRot)*dTime*100;
            angularVelocity *= 0.9;
            rot += angularVelocity * dTime;


            float speed = 2*prevPower;
            float density = prevPower;

            prevTip = tip;
            tip.x = pos.x+cos((rot-90)*DEG_TO_RAD)*30;
            tip.y = pos.y+sin((rot-90)*DEG_TO_RAD)*30;

            smoke.update(dTime, tip, prevTip, rot, prevRot, density, speed);


    }

    void update (
        float dTime,
        float power
        ) {
        update(dTime, power, this->rot, this->pos);
    }

    void update (
        float dTime,
        float power,
        float rotation
        ) {
        update(dTime, power, rotation, this->pos);
    }


    virtual void draw (
            sf::RenderTarget& target,
            sf::RenderStates states
        ) const {

        target.draw(smoke);
        
        const float whiter = 15;
        const float redr = 12;

        sf::CircleShape whitebg;
        sf::ConvexShape whitetip;
        sf::RectangleShape whiterect;
        sf::RectangleShape redrect;
        sf::CircleShape redcenter;
        sf::ConvexShape redtip;


        whitebg.setOrigin({whiter,whiter});
        whitebg.setRadius(whiter);
        whitebg.setFillColor(sf::Color(0xffcc00ff));
        whitebg.setPosition(pos);

        redcenter.setOrigin({redr,redr});
        redcenter.setRadius(redr);
        redcenter.setFillColor(sf::Color(0x9966ffff));
        redcenter.setPosition(pos);
  
        whitetip.setPointCount(3);
        whitetip.setPoint(0,{
            pos.x+cos((rot-60-90)*DEG_TO_RAD)*whiter,
            pos.y+sin((rot-60-90)*DEG_TO_RAD)*whiter
        });
        whitetip.setPoint(1,{
            pos.x+cos((rot+60-90)*DEG_TO_RAD)*whiter,
            pos.y+sin((rot+60-90)*DEG_TO_RAD)*whiter
        });
        whitetip.setPoint(2,tip);
        whitetip.setFillColor(sf::Color(0xffcc00ff));
        
        target.draw(whitebg);
        target.draw(whitetip);
        // target.draw(whiterect);
        target.draw(redcenter);
        // target.draw(redrect);
        // target.draw(redtip);

    }
};