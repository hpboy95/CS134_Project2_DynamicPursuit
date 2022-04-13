#pragma once

#include "ofMain.h"

class ParticleForceField;

class Particle {
public:
	Particle();

	glm::vec3 acceleration;
	float mass;
	glm::vec3 position;
	float velocity;
	float damping;
	glm::vec3 heading;
	glm::vec3 forces;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    draw();
	float   age();        // sec
	void integrate();
	ofColor color;
};


