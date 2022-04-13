#include "RadiusEmitter.h"

void RadiusEmitter::update() {
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
	vector<glm::vec3> playerVerts = target->verts;


	if ((time - lastSpawned) > (1000.0 / rate)) {

		// call virtual to spawn a new sprite
		//
		spawnSprite();
		lastSpawned = time;
	}



	// update sprite list
	//
	if (sys->sprites.size() == 0) return;
	vector<Sprite>::iterator s = sys->sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sys->sprites.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//cout << "deleting sprite: " << s->name << endl;
			tmp = sys->sprites.erase(s);
			s = tmp;
		}
		else {
			//Check for collisions with player
			bool updated = false;
			glm::vec3 asteroidPos = s->getPos();
			float asteroidWidth = s->spriteImage.getWidth();
			float distance = glm::distance(asteroidPos, target->getPos());
			float contactDistance = asteroidWidth / 2 + target->mySprite.getWidth() / 2;
			if (distance < contactDistance) {
				//Collision with Player
				tmp = sys->sprites.erase(s);
				s = tmp;
				updated = true;
				target->dealDamage(1);
				explosions->setPos(s->pos);
				explosions->start();
			}
            //Check for collisions with the bullets if you didnt collide with player
            vector<Particle>::iterator bullets = target->gun.sys->bullets.begin();
            vector<Particle>::iterator tmpBullet;
            while (!updated && bullets != target->gun.sys->bullets.end()){
                distance = glm::distance(bullets->position, asteroidPos);
                contactDistance = asteroidWidth / 2 + bullets->radius;
                bool deleted = false;
                if (distance < contactDistance) {
                    tmpBullet = target->gun.sys->bullets.erase(bullets);
                    bullets = tmpBullet;
                    deleted = true;
                    tmp = sys->sprites.erase(s);
                    s = tmp;
                    updated = true;
					explosions->setPos(s->pos);
					explosions->start();
                }
                if (!deleted){
                    bullets++;
                }
            }
			//Go To next asteroid
			if (!updated) {
				s++;
			}
		}
			
	}


	for (int i = 0; i < sys->sprites.size(); i++) {
		moveSprite(&sys->sprites[i]);
	}
}

void RadiusEmitter::moveSprite(Sprite* sprite) {
	sprite->setPos(sprite->getPos() + (sprite->velocity / ofGetFrameRate()) * sprite->getHeading());
}

// virtual function to spawn sprite (can be overloaded)
//
void RadiusEmitter::spawnSprite() {
	Sprite sprite;
	if (haveChildImage) sprite.setImage(childImage);
	sprite.velocity = velocity;
	sprite.lifespan = lifespan;
	//Set random position around target
	int random_x = rand() % ofGetWidth();
	int random_y = rand() % ofGetHeight();
	//TODO this code makes program crash
	//Make sure that the x and y are away from the target
	/*
	while (random_x < target->getPos().x + spawnRadius && random_x > target->getPos().x - spawnRadius) {
		int random_x = rand() % ofGetWidth();
	}
	while (random_y < target->getPos().y + spawnRadius && random_y > target->getPos().y - spawnRadius) {
		int random_y = rand() % ofGetHeight();
	}
	*/
	sprite.setPos(glm::vec3(random_x, random_y, getPos().z));
    glm::vec3 toTarget = glm::normalize(sprite.getPos() - target->getPos());
    sprite.heading = toTarget;
	sprite.birthtime = ofGetElapsedTimeMillis();
	sys->add(sprite);
}
