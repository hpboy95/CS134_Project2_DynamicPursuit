#pragma once

#include "ofMain.h"

class ParticleForceField;

class Particle {
public:
	Particle();

	ofVec3f position;
	float velocity;
	glm::vec3 heading;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    draw();
	float   age();        // sec
	ofColor color;
};


