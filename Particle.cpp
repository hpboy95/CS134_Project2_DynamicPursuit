#include "Particle.h"


Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity = 800;
	position = glm::vec3(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 10;
	color = ofColor::aquamarine;
}

void Particle::draw() {
	ofSetColor(color);
	ofDrawSphere(position, radius);
}

//  return age in seconds
//
float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime)/1000.0;
}


