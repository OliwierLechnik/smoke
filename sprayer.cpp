#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "smoke.cpp"

class Sprayer : public sf::Drawable {

    sf::Vector2f pos; // center of mass
    sf::Vector2f tip; // place where the smoke is commit from
    float rot; // rotation

    Smoke smoke;

    public:

    Sprayer () : pos({0,0}), rot(0) { }
    Sprayer (sf::Vector2f position, float rotation) : pos(position), rot(rotation) { }

    void update (
        float dTime, 
        float dencity,
        float speed,
        float rotation, 
        sf::Vector2f position
        ) {
            pos = position;
            rot = rotation;

            
            tip.x = pos.x+cos((rot-90)*DEG_TO_RAD)*30;
            tip.y = pos.y+sin((rot-90)*DEG_TO_RAD)*30;

    }

    void update (
        float dTime,
        float dencity,
        float speed
        ) {
        update(dTime, dencity, speed, rot, pos);
    }

    void update (
        float dTime,
        float dencity,
        float speed,
        float rotation
        ) {
        update(dTime, dencity, speed, rotation, pos);
    }


    virtual void draw (
            sf::RenderTarget& target,
            sf::RenderStates states
        ) const {
        
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
        whitebg.setFillColor(sf::Color::White);
        whitebg.setPosition(pos);

        redcenter.setOrigin({redr,redr});
        redcenter.setRadius(redr);
        redcenter.setFillColor(sf::Color::Red);
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
        whitetip.setFillColor(sf::Color::White);
        
        target.draw(whitebg);
        target.draw(whitetip);
        // target.draw(whiterect);
        target.draw(redcenter);
        // target.draw(redrect);
        // target.draw(redtip);

    }
};