#pragma once

#include "Emitter.h"
#include "ParticleEmitter.h"
#include "./Shapes/player.h"


class RadiusEmitter : public Emitter {
public:
    RadiusEmitter(Player *target, ParticleEmitter *explosions, int radius, ofSoundPlayer *explodeSound) {
        this->target = target;
        this->explosions = explosions;
        this->explodeSound = explodeSound;
        spawnRadius = radius;
        haveChildImage = false;
    }
    int spawnRadius;
    Player *target;
    ParticleEmitter *explosions;
    ofSoundPlayer *explodeSound;

    void moveSprite(Sprite* sprite);
    void spawnSprite();
    void update();
    void split(int stage, glm::vec3 heading, glm::vec3 position);


};


