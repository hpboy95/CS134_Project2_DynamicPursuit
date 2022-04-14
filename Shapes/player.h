/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#pragma once
#include "triangleShape.h"
#include "../BulletEmitter.h"

class Player : public TriangleShape {
public:
    Player() {

    }

    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, ofImage sprite, ofSoundPlayer& s1, ofSoundPlayer& s2) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
        mySprite = sprite;
        shoot1 = s1;
        shoot2 = s2;
    }
    void draw();
    void drawSprite();
    bool inside(glm::vec3 p);
    glm::vec3 getCenter();

    glm::vec3 getHeading();
    void setHeading(glm::vec3 heading) {
        this->heading = heading;
    }

    bool hasSprite = false;

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

    void update(int health, glm::vec3 scale, bool sprite);

    void addSounds(ofSoundPlayer &s1, ofSoundPlayer &s2) {
        shoot1 = s1;
        shoot2 = s2;
    }

    ofImage mySprite;

    //  Integrator Function;
    //
    void integrate();

    // Physics data goes here  (for integrate() );
    //
    glm::vec3 velocity = glm::vec3(0, 0, 0);
    glm::vec3 acceleration = glm::vec3(0, 0, 0);
    glm::vec3 force = glm::vec3(0, 0, 0);
    float mass = 1.0;
    float damping = .99;
    float angularForce = 0;
    float angularVelocity = 0.0;
    float angularAcceleration = 0.0;
    bool bThrust = false;
    bool collision = false;
    float prevDist = 0;
    float lastShot = 0;
    ofSoundPlayer shoot1;
    ofSoundPlayer shoot2;
    BulletEmitter gun;
    void shoot();


private:
    glm::vec3 heading = glm::vec3(0, -1, 0);
    int maxHealth = 100;
    int damageTaken = 0;

};
