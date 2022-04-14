#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "RadiusEmitter.h"
#include "BulletEmitter.h"
#include "ParticleEmitter.h"
#include "./Shapes/player.h"
#include <ctime>;

class Agent : public Sprite {

};

class AgentEmitter : public Emitter {
public:
	void moveSprite(Sprite* sprite) {
		Emitter::moveSprite(sprite);
	}
	void spawnSprite() {
		Emitter::spawnSprite();
	}
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void drawHeading();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		float framerate = 60;
		float baseSpeed = 60;
		float baseRotation = 0.5;

		map<string, bool> keysPressed;

		vector<Emitter *> emitters;
		int numEmitters;
    
        //Prep Explosions
        ParticleEmitter *explosions;

		//Set Images
		ofImage playerSprite;
		ofImage enemySprite;
		ofImage background;
		ofImage asteroid;
		bool imageLoaded;

		//Set Sounds
		ofSoundPlayer backgroundSound;
		ofSoundPlayer *explodeSound;
		bool soundLoaded;

		ofVec3f mouse_last;
		bool start = false;
		bool gameOver = false;

		//GUI
		ofxPanel gui;
		ofxIntSlider spawners;
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxToggle showHeading;
		ofxFloatSlider scaleSlider;
		ofxIntSlider playerLife;
		ofxToggle showSprite;
		ofxLabel screenSize;
		ofxFloatSlider restitution;
		ofxFloatSlider thrust;
		ofTrueTypeFont font;
		bool showHUD;
		time_t time_start, time_finish;

		//Player
		Player* player;
};
