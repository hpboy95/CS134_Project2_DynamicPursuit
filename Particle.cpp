#include "Particle.h"


Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity = 800;
	acceleration = glm::vec3(0, 0, 0);
	position = glm::vec3(0, 0, 0);
	forces = glm::vec3(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 10;
	damping = 0.99;
	mass = 1.0;
	color = ofColor::aquamarine;
}

void Particle::draw() {
	ofSetColor(color);
	ofDrawSphere(position, radius);
}

void Particle::integrate() {


	// interval for this step
	//
	float dt = 1.0 / ofGetFrameRate();

	// update position based on velocity
	//
	position += (velocity * dt);


	// add a little damping for good measure
	//
	velocity *= damping;

	// clear forces on particle (they get re-added each step)
	//
	forces = glm::vec3(0, 0, 0);
}

//  return age in seconds
//
float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime)/1000.0;
}


