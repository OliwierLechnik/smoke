#pragma once

#include "utensils.cpp"

class Smoke : public sf::Drawable {

    struct Particle {

        // some constants for easy editon in the future
        constexpr static const float airFriction = 0.03;
        constexpr static const float upwardForce = 0;
        constexpr static const float angularFriction = 1.2;
        constexpr static const int angleRandomness = 15; // max deviation in each direction. [degrees] 
        constexpr static const int sizeRandomness = 50; // +- max deviation in size. [percentage]
        constexpr static const int speedRandomness = 30; // +- max deviation in speed. [percentage]
        constexpr static const float maxLifetime = 3;
        constexpr static const float scaleGrowthFactor = 1; // 

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
                sin(angle*DEG_TO_RAD)*speed,
                -cos(angle*DEG_TO_RAD)*speed
            };

            float scaleRand = 1 + (rand()%(2*sizeRandomness)-sizeRandomness) / 100.f;

            this->scale = {
                size * scaleRand,
                size * scaleRand
            };

            this->rotation = rand()%36000/100.f;

            this-> wVel = rand()%144000/100.f-720.f;

            this->lifetime = 0.f;

            this->update(rand()%(int)(dTime*100)/100.f);
        }

        float getLifetimeRatio ( ) {
            return lifetime / maxLifetime;
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

        sf::Vector2f getScale ( ) {
            return scale * lifetime * scaleGrowthFactor;
        }

    };


    std::vector <Particle> particles;
    sf::Texture txt;

public:

    Smoke ( ) {
        txt.loadFromFile("smoke.png");
    }

    void update(
            float dTime,
            sf::Vector2f pos,
            float direction,
            float density, // (averege) smoke particles per second
            float speed
        ) {

            // #1 update all particles (if particle lifetime is higher than max lifetime. kill particle)
            // #2 decide how much new particles to make
            // #3 make those particles

        // #1
        // for(std::vector<Particle>::iterator particle = particles.begin(); particle != particles.end(); ){
        //     if(particle->lifetime >= maxLifetime){
        //         particle = particles.erase(particle);
        //     } else {
        //         particle->update(dTime);
        //         particle++;
        //     }
        // }

        for(Particle& i : particles){
            i.update(dTime);
        }

        remove_erase_if(particles, [](Particle& ptr)->bool{
            if(ptr.getLifetimeRatio() >= 1){
                return true;
            }
            return false;
        });
        
        // #2
        float nptm = dTime * density; // amount of new particles to make
        int confident = floor(nptm);
        float poap = nptm - (float)confident; // propability of aditional particle
        
        if(rand()%1000/1000.f <= poap) confident += 1;

        // #3
        for(int i = 0; i < confident; i++){
            particles.emplace_back(
                pos,
                speed,
                direction,
                0.1,
                dTime
            );
        }

    }

    virtual void draw(
            sf::RenderTarget& target,
            sf::RenderStates states
        ) const {

        sf::Sprite sprite;
        sprite.setTexture(txt);
        sprite.setOrigin({
            sprite.getTextureRect().width/2,
            sprite.getTextureRect().height/2,
        });
        
        for(Particle i : particles){
            float ratio = i.getLifetimeRatio();

            sprite.setPosition(i.pos);
            sprite.setScale(i.getScale());
            sprite.setRotation(i.rotation);
            sprite.setColor(sf::Color(255,255,255,40-40*ratio+1));

            target.draw(sprite);
        }

    }

};