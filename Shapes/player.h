/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#pragma once
#include "triangleShape.h"

class Player : public TriangleShape {
public:
    Player() {

    }
    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, ofImage sprite) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
        mySprite = sprite;
        damageTaken = 0;
        maxHealth = 100;

    }
    void draw();
    void drawSprite();
    bool inside(glm::vec3 p);
    glm::vec3 getCenter();

    glm::vec3 getHeading();
    void setHeading(glm::vec3 heading) {
        this->heading = heading;
    }

    bool hasSprite;

    int getHealth() {
        return maxHealth;
    }

    void setHealth(int hp) {
        maxHealth = hp;
    }

    int getDamage() {
        return damageTaken;
    }

    void dealDamage(int damage) {
        damageTaken += damage;
    }

    ofImage mySprite;

private:
    glm::vec3 heading = glm::vec3(0, -1, 0);
    int maxHealth;
    int damageTaken;

};
