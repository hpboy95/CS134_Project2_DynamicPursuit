#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	//Load Fonts
	font.load("./fonts/OpenSans-Semibold.ttf", 50);
	
	//Load Images
	// create an image for sprites being spawned by emitter
	//
	if (playerSprite.load("images/spaceship.png")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open image file" << endl;
		ofExit();
	}
	if (enemySprite.load("images/asteroid-pixel-art-maker-514800.png")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open image file" << endl;
		ofExit();
	}
	if (background.load("images/408-0.png")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open image file" << endl;
		ofExit();
	}
    if (asteroid.load("images/asteroid-pixel-art-maker-514800.png")){
        imageLoaded = true;
    }
    else {
        cout << "Can't open image file" << endl;
        ofExit();
    }

	ofSoundPlayer& shoot1Sound = ofSoundPlayer();
	ofSoundPlayer& shoot2Sound = ofSoundPlayer();
	explodeSound = new ofSoundPlayer();
	thrustSound = new ofSoundPlayer();
	//LoadSounds
	if (backgroundSound.load("sounds/Hardmoon_-_Deep_space.mp3")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open sound file" << endl;
		ofExit();
	}
	if (thrustSound->load("sounds/ScatterNoise1.mp3")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open sound file" << endl;
		ofExit();
	}
	if (shoot1Sound.load("sounds/laserfire01.ogg")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open sound file" << endl;
		ofExit();
	}
	if (shoot2Sound.load("sounds/laserfire02.ogg")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open sound file" << endl;
		ofExit();
	}
	if (explodeSound->load("sounds/explosion.wav")) {
		imageLoaded = true;
	}
	else {
		cout << "Can't open sound file" << endl;
		ofExit();
	}
	thrustSound->setLoop(true);
	explodeSound->setVolume(0.50);
	backgroundSound.setLoop(true);
	backgroundSound.play();


	//Setup Player
	player = new Player(glm::vec3(-50, 50, 0), glm::vec3(50, 50, 0), glm::vec3(0, -50, 0), playerSprite, shoot1Sound, shoot2Sound);
	player->setPos(glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	player->setRotation(0);
	player->setScale(glm::vec3(1, 1, 1));
	player->setColor(ofColor::orange);
	keysPressed["up"] = false;
	keysPressed["down"] = false;
	keysPressed["left"] = false;
	keysPressed["right"] = false;

	// create an array of emitters and set their position;
	//
	
	//	turret = new Emitter();
    
    //Prepare Explosion
    ImpulseRadialForce *radial = new ImpulseRadialForce(1000);
    explosions = new ParticleEmitter();
    explosions->particleRadius = 5;
    explosions->setEmitterType(RadialEmitter);
    explosions->setVelocity(glm::vec3(1000));
    explosions->setOneShot(true);
    explosions->setGroupSize(100);
    explosions->lifespan = 2;
    explosions->sys->addForce(radial);

	Emitter *temp = new RadiusEmitter(player, explosions, 50, explodeSound);

	temp->setPos(glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	temp->drawable = false;
	temp->setChildImage(enemySprite);
	temp->start();

	emitters.push_back(temp);
	numEmitters ++;
    
	//GUI
	//HUD
	gui.setup();
	gui.add(spawners.setup("Number Of Spawners", 1, 1, 10));
	gui.add(rate.setup("rate", 0.5, 0.5, 10));
	gui.add(life.setup("life", 5, 0.0, 10));
	gui.add(velocity.setup("velocity", ofVec3f(-200, -200, 0), ofVec3f(-200, -200, 0), ofVec3f(1000, 1000, 1000)));
	//In pixels per second
	gui.add(scaleSlider.setup("Scale Slider", 1.0, 0.1, 5.0));
	gui.add(playerLife.setup("Player Health", 20, 0, 100));
	gui.add(showHeading.setup("Show Heading", false));
	gui.add(showSprite.setup("Show Sprite", true));
	gui.add(thrust.setup("Thrust", 800, 100, 1000));
	gui.add(restitution.setup("Restitution", .85, 0.0, 1.0));
	showHUD = false;
	//Additional GUI
}

//--------------------------------------------------------------
void ofApp::update() {
	if (start) {
		//Add new Spawners
		if (spawners != numEmitters) {
			while (spawners > numEmitters) {
				RadiusEmitter* temp = new RadiusEmitter(player, explosions, 50, explodeSound);
				temp->setPos(glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
				temp->drawable = false;
				temp->setChildImage(enemySprite);
				temp->start();

				emitters.push_back(temp);
				numEmitters++;
			}

			while (spawners < numEmitters) {
				vector<Emitter*>::iterator s = emitters.begin();
				vector<Emitter*>::iterator tmp;
				tmp = emitters.erase(s);
				s = tmp;
				numEmitters--;
			}
		}

		player->update(playerLife, glm::vec3(scaleSlider), showSprite);

		//Update Emitters
		for (int i = 0; i < emitters.size(); i++) {
			emitters[i]->haveChildImage = showSprite;
			emitters[i]->setRate(rate);
			emitters[i]->setLifespan(life * 1000);    // convert to milliseconds 
			emitters[i]->setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
			emitters[i]->update();
		}
        
        explosions->update();

		if (keysPressed["up"]) {
			player->force = player->force + (float)thrust * player->getHeading();
		}
		if (keysPressed["down"]) {
			player->force = player->force - (float)thrust * player->getHeading();
		}
		if (keysPressed["left"]) {
			player->angularForce -= (float)thrust / 5;
		}
		if (keysPressed["right"]) {
			player->angularForce += (float)thrust / 5;
		}
		if (keysPressed["space"]) {
			player->shoot();
		}

		if (keysPressed["up"] || keysPressed["down"] || keysPressed["left"] || keysPressed["right"]) {
			playThrust = true;
		}
		else {
			playThrust = false;
		}

		if (!playThrust) {
			thrustSound->play();
		}
		else {
			//thrustSound->stop();
		}

		//Game over check
		if (player->getHealth() - player->getDamage() <= 0) {
			if (!gameOver) {
				time(&time_finish);
			}
			gameOver = true;
		}

	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	//Always Draw the Background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());
	//Game Over Screen
	if (gameOver) {
		for (int i = 0; i < emitters.size(); i++) {
			emitters[i]->stop();
		}

		ofSetColor(ofColor::orange);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 - 80);
		int difference = difftime(time_finish, time_start);
		int minutes = difference / 60;
		int seconds = difference % 60;
		string text = "Game Over";
		float fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();
		char buffer[100];
		if (minutes > 0) {
			snprintf(buffer, 100, "You Survived %d Minutes and %02d Seconds", minutes, seconds);
		}
		else {
			snprintf(buffer, 100, "You Survived %d Seconds", seconds);
		}
		ofSetColor(ofColor::orange);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		fontWidth = font.stringWidth(buffer);
		font.drawString(buffer, -fontWidth / 2, 0);
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 + 80);
		text = "Score: " + to_string(player->score);
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 + 160);
		text = "Restart to Continue";
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();
	}
	//Start Screen
	if (!start) {
		ofSetColor(ofColor::orange);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

		string text = "Press Space to Start";
		float fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();
	}
	//Regular Game State
	if (start && !gameOver){
		//Draw the time
		ofSetColor(ofColor::white);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() - 0.92 * ofGetHeight());
		time(&time_finish);
		int difference = difftime(time_finish, time_start);
		int minutes = difference / 60;
		int seconds = difference % 60;
		char buffer[100];
		if (minutes > 0) {
			snprintf(buffer, 100, "%d : %02d", minutes, seconds);
		}
		else {
			snprintf(buffer, 100, "%d", seconds);
		}
		float fontWidth = font.stringWidth(buffer);
		font.drawString(buffer, -fontWidth / 2, 0);
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() - 0.92 * ofGetHeight() + 80);
		string text = "Score:  " + to_string(player->score);
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();

		//Draw FPS
		int fps = ofGetFrameRate();
		ofSetColor(ofColor::white);
		ofPushMatrix();
		ofTranslate(ofGetWidth() - 0.15 * ofGetWidth(), ofGetHeight() - 0.92 * ofGetHeight());
		text = "FPS " + to_string(fps);
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();

		//HealthBar
		ofSetColor(ofColor::red);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() - 0.05 * ofGetHeight() - 60);
		text = "Health";
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();
		double redFrac = player->getHealth() - player->getDamage()/ player->getHealth();
		double blue = 1 - redFrac;
		ofSetColor(ofColor::red);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() - 0.05 * ofGetHeight());
		text = to_string(player->getHealth() - player->getDamage()) + "/" +  to_string(player->getHealth());
		fontWidth = font.stringWidth(text);
		font.drawString(text, -fontWidth / 2, 0);
		ofPopMatrix();



		//Draw Player and other sprites
		for (int i = 0; i < emitters.size(); i++) {
			emitters[i]->draw();
		}
        explosions->draw();
		player->draw();
		if (showHeading) {
			drawHeading();
		}
		if (showHUD) {
			gui.draw();
		}
		ofSetColor(ofColor::white);
	}
}


/*
* Draws the heading of the player
*/
void ofApp::drawHeading() {
	ofSetColor(ofColor::black);
	glm::vec3 start = player->getCenter();
	glm::vec3 end = start + 75 * player->getHeading();
	ofPushMatrix();
	ofMultMatrix(player->getTranslationMatrix());
	//Draw the main line
	ofDrawLine(start, end);
	//Draw side arrows
	//Draw left
	glm::mat4 leftrotation = glm::rotate(glm::mat4(1.0), glm::radians(30.0f), glm::vec3(0, 0, 1));
	glm::vec3 leftRotatedHeading = glm::normalize(glm::vec3(leftrotation * glm::vec4(player->getHeading(), 1)));
	glm::vec3 leftEnd = end - 15 * leftRotatedHeading;
	ofDrawLine(end, leftEnd);
	//Draw right
	glm::mat4 rightRotation = glm::rotate(glm::mat4(1.0), glm::radians(-30.0f), glm::vec3(0, 0, 1));
	glm::vec3 rightRotatedHeading = glm::normalize(glm::vec3(rightRotation * glm::vec4(player->getHeading(), 1)));
	glm::vec3 rightEnd = end - 15 * rightRotatedHeading;
	ofDrawLine(end, rightEnd);
	ofPopMatrix();
}

//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
        explosions->sys->reset();
        cout << "exploding" <<endl;
        explosions->start();
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		showHUD = !showHUD;
		break;
	case 'r':
		break;
	case 's':
		break;
	case 'u':
		break;
	case ' ':
	{
		if (!start) {
			start = true;
			time(&time_start);
		}
		keysPressed["space"] = true;
		break;
	}
	case OF_KEY_UP:
	{
		keysPressed["up"] = true;
		break;
	}
	case OF_KEY_DOWN:
	{
		keysPressed["down"] = true;
		break;
	}
	case OF_KEY_LEFT:
	{
		keysPressed["left"] = true;
		break;
	}
	case OF_KEY_RIGHT:
	{
		keysPressed["right"] = true;
		break;
	}
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_LEFT:
	{
		keysPressed["left"] = false;
		break;
	}
	case OF_KEY_RIGHT:
	{
		keysPressed["right"] = false;
		break;
	}
	case OF_KEY_UP:
	{
		keysPressed["up"] = false;
		break;
	}
	case OF_KEY_DOWN:
	{
		keysPressed["down"] = false;
		break;
	}
	case ' ':
	{
		keysPressed["space"] = false;
		break;
	}
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

