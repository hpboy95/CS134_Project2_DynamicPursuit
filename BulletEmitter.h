#pragma once

#include "ofMain.h"
#include "./Shapes/shape.h"
#include "Particle.h"

//
//  Manages all Bullets in a system.
//
class BulletList {
public:
	void add(Particle);
	void remove(int);
	void update();
	void draw();
	vector<Particle> bullets;
};


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class BulletEmitter : public Shape {
public:
	BulletEmitter();
	void init();
	void draw();
	virtual void update();

	void moveSprite(Particle*);
	void spawnSprite(glm::vec3 p, glm::vec3 heading);

	BulletList* sys;
	glm::vec3 velocity;
	float lifespan;
	float lastSpawned;
	float radius;
};

