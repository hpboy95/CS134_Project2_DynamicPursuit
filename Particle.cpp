#include "Particle.h"


Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity = glm::vec3(0);
    acceleration = glm::vec3(0);
	position = glm::vec3(0, 0, 0);
    forces = glm::vec3(0);
	lifespan = 5;
	birthtime = 0;
	radius = 10;
    damping = .99;
    mass = 1;
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
    position += (velocity * heading * dt);

    // update acceleration with accumulated paritcles forces
    // remember :  (f = ma) OR (a = 1/m * f)
    //
    glm::vec3 accel = acceleration;    // start with any acceleration already on the particle
    accel += (forces * (1.0 / mass));
    velocity += accel * dt;
    
    // add a little damping for good measure
    //
    velocity *= damping;

    // clear forces on particle (they get re-added each step)
    //
    forces = glm::vec3(0);
}

//  return age in seconds
//
float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime)/1000.0;
}


