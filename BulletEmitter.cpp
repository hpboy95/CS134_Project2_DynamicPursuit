#include "ofApp.h"
//----------------------------------------------------------------------------------
//
// This example code demonstrates the use of an "Emitter" class to emit Sprites
// and set them in motion. The concept of an "Emitter" is taken from particle
// systems (which we will cover next week).
//
// The Sprite class has also been upgraded to include lifespan, velocity and age
// members.   The emitter can control rate of emission and the current velocity
// of the particles. In this example, there is no acceleration or physics, the
// sprites just move simple frame-based animation.
//
// The code shows a way to attach images to the sprites and optional the
// emitter (which is a point source) can also have an image.  If there are
// no images attached, a placeholder rectangle is drawn.
// Emitters  can be placed anywhere in the window. In this example, you can drag
// it around with the mouse.
//
// OF has an add-in called ofxGUI which is a very simple UI that is useful for
// creating sliders, buttons and fields. It is not recommended for commercial 
// game development, but it is useful for testing.  The "h" key will hide the GUI
// 
// If you want to run this example, you need to use the ofxGUI add-in in your
// setup.
//
//
//  Kevin M. Smith - CS 134 SJSU




//  Add a Sprite to the Sprite System
//
void BulletList::add(Particle s) {
	bullets.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void BulletList::remove(int i) {
	bullets.erase(bullets.begin() + i);
}


//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void BulletList::update() {

	if (bullets.size() == 0) return;
	vector<Particle>::iterator s = bullets.begin();
	vector<Particle>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != bullets.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = bullets.erase(s);
			s = tmp;
		}
		else s++;
	}

	//  Move sprite
	//
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].position += bullets[i].velocity / ofGetFrameRate();
	}
}

//  Render all the sprites
//
void BulletList::draw() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw();
	}
}

BulletEmitter::BulletEmitter() {
	sys = new BulletList();
	init();
}


void BulletEmitter::init() {
	lifespan = 6000;    // default milliseconds
	lastSpawned = 0;
	radius = 0.2;
}



//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void BulletEmitter::draw() {
	// draw sprite system
	//
	sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void BulletEmitter::update() {
	float time = ofGetElapsedTimeMillis();
	// update sprite list
	//
	if (sys->bullets.size() == 0) return;
	vector<Particle>::iterator s = sys->bullets.begin();
	vector<Particle>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sys->bullets.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sys->bullets.erase(s);
			s = tmp;
		}
		else s++;
	}


	for (int i = 0; i < sys->bullets.size(); i++) {
		moveSprite(&sys->bullets[i]);
	}

}

// virtual function to move sprite (can be overloaded)
//
void BulletEmitter::moveSprite(Particle* particle) {
	particle->position = particle->position + 1000 * particle->heading / ofGetFrameRate();
}

// virtual function to spawn sprite (can be overloaded)
//
void BulletEmitter::spawnSprite(glm::vec3 p, glm::vec3 heading) {
	Particle particle;
	particle.heading = heading;
	particle.position = p;
	particle.birthtime = ofGetElapsedTimeMillis();
	sys->add(particle);
}
