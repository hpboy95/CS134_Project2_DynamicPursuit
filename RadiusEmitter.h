#pragma once

#include "Emitter.h"
#include "ParticleEmitter.h"
#include "./Shapes/player.h"


class RadiusEmitter : public Emitter {
public:
    RadiusEmitter(Player *target,ParticleEmitter *explosions, int radius) {
        this->target = target;
        this->explosions = explosions;
        spawnRadius = radius;
        haveChildImage = false;
    }
    int spawnRadius;
    Player *target;
    ParticleEmitter* explosions;
    

    void moveSprite(Sprite* sprite);
    void spawnSprite();
    void update();


};


