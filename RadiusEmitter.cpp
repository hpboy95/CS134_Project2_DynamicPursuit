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

	//Add the split sprites
	vector<Sprite>::iterator spawning = toSpawn.sprites.begin();
	vector<Sprite>::iterator spawns;
	while (spawning != toSpawn.sprites.end()) {
		sys->add(*spawning);
		spawns = toSpawn.sprites.erase(spawning);
		spawning = spawns;
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
			bool splitting = false;
			glm::vec3 asteroidPosition = s->getPos();
			float asteroidWidth = s->spriteImage.getWidth();
			glm::vec3 heading = s->heading;
			glm::vec3 scale = s->getScale();
			int stage = s->stage;
			float distance = glm::distance(asteroidPosition, target->getPos());
			float contactDistance = asteroidWidth / 2 + target->mySprite.getWidth() / 2;
			if (distance < contactDistance) {
				tmp = sys->sprites.erase(s);
				s = tmp;
				updated = true;
				target->dealDamage(stage);
                explosions->pos = asteroidPosition;
                explosions->start();
				explodeSound->play();
			}
            //Check for collisions with the bullets if you didnt collide with player
            vector<Particle>::iterator bullets = target->gun.sys->bullets.begin();
            vector<Particle>::iterator tmpBullet;
            while (!updated && bullets != target->gun.sys->bullets.end()){
                distance = glm::distance(bullets->position, asteroidPosition);
                contactDistance = asteroidWidth / 2 + bullets->radius;
                bool deleted = false;
                if (distance < contactDistance) {
                    tmpBullet = target->gun.sys->bullets.erase(bullets);
                    bullets = tmpBullet;
                    deleted = true;
					explosions->pos = asteroidPosition; //Explode then delete
					explosions->start();
                    tmp = sys->sprites.erase(s);
                    s = tmp;
                    updated = true;
					explodeSound->play();
					if (stage != 0) {
						splitting = true;
					}
                }
                if (!deleted){
                    bullets++;
                }
            }
			//Update Agent Position
			if (!updated) {
				s++;
			}
			if (splitting) {
				split(stage, heading, asteroidPosition, scale);
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

void RadiusEmitter::split(int stage, glm::vec3 heading, glm::vec3 position, glm::vec3 scale) {
	Sprite sprite1; 
	Sprite sprite2;
	//Sprite1 stuff
	sprite1.stage = stage - 1;
	if (haveChildImage) sprite1.setImage(childImage);
	sprite1.velocity = velocity;
	sprite1.lifespan = lifespan;
	sprite1.setPos(position);
	sprite1.setScale(0.5 * scale);
	sprite1.heading = -heading;
	sprite1.rotation += 45;
	sprite1.birthtime = ofGetElapsedTimeMillis();

	//Sprite2 stuff
	sprite2.stage = stage - 1;
	if (haveChildImage) sprite2.setImage(childImage);
	sprite2.velocity = velocity;
	sprite2.lifespan = lifespan;
	sprite2.setPos(position);
	sprite2.setScale(0.5 * scale);
	sprite2.heading = -heading;
	sprite2.rotation -= 45;
	sprite2.birthtime = ofGetElapsedTimeMillis();

	toSpawn.add(sprite1);
	toSpawn.add(sprite2);
}