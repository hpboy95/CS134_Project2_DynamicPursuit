#pragma once

#include "Emitter.h"
#include "./Shapes/player.h"


class RadiusEmitter : public Emitter {
public:
    RadiusEmitter(Player *target, int radius) {
        this->target = target;
        spawnRadius = radius;
        haveChildImage = false;
    }
    int spawnRadius;
    Player *target;
    

    void moveSprite(Sprite* sprite);
    void spawnSprite();
    void update();


};


