#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"


//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
protected:
public:
	bool applyOnce = false;
	bool applied = false;
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
	void setLifespan(float);
	void reset();
	int removeNear(const ofVec3f & point, float dist);
	void draw();
	vector<Particle> particles;
	vector<ParticleForce *> forces;
};



// Some convenient built-in forces
//
class GravityForce: public ParticleForce {
	glm::vec3 gravity;
public:
	GravityForce(const glm::vec3 & gravity);
	void updateForce(Particle *);
};

class TurbulenceForce : public ParticleForce {
	glm::vec3 tmin, tmax;
public:
	TurbulenceForce(const glm::vec3 & min, const glm::vec3 &max);
	void updateForce(Particle *);
};

class ImpulseRadialForce : public ParticleForce {
	float magnitude;
public:
	ImpulseRadialForce(float magnitude); 
	void updateForce(Particle *);
};

class RadialForce : public ParticleForce {
	float magnitude;
	float thickness;
public:
	RadialForce(float magnitude, float thickness);
	void updateForce(Particle*);
	void setThickness(float thickness);
};

class CyclicForce : public ParticleForce {
	float rotation;
	float magnitude;
public:
	CyclicForce(float magnitude, float rotation);
	void updateForce(Particle*);
	void setRotation(float rotation);
};

