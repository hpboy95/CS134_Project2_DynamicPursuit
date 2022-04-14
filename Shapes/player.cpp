/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#include "player.h"

/*
 Returns the heading for the player
 */
glm::vec3 Player::getHeading() {
    return glm::normalize(glm::vec3(getRotationMatrix() * glm::vec4(heading, 1)));
}

/*
 Essentially the same inside function as Triangle Shape
 */
bool Player::inside(glm::vec3 p) {
    //Convert the mouse to object space
    glm::vec3 inverted = glm::vec3(glm::inverse(getMatrix()) * glm::vec4(p, 1.0f));
    //Gets all of the vectors from point to verticies
    glm::vec3 v1 = glm::normalize(verts[0] - inverted);
    glm::vec3 v2 = glm::normalize(verts[1] - inverted);
    glm::vec3 v3 = glm::normalize(verts[2] - inverted);
    //Gets the angles between all vectors and checks that they are all facing the same way
    float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
    float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
    float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
    if (a1 < 0 && a2 < 0 && a3 < 0) return true;
    else return false;
}

/*
 Player Draw function
 Using Ofx Draw
 */
void Player::draw() {
    //Constrict to screen
    if (getPos().x > ofGetWidth()) {
        setPos(glm::vec3(ofGetWidth(), getPos().y, getPos().z));
    }
    if (getPos().x < 0) {
        setPos(glm::vec3(0.0, getPos().y, getPos().z));
    }
    if (getPos().y > ofGetHeight()) {
        setPos(glm::vec3(getPos().x, ofGetHeight(), getPos().z));
    }
    if (getPos().y < 0) {
        setPos(glm::vec3(getPos().x, 0, getPos().z));
    }
    if (hasSprite) {
        drawSprite();
    }
    else {
        ofSetColor(getColor());
        ofFill();
        ofPushMatrix();
        ofMultMatrix(getMatrix());
        ofDrawTriangle(verts[0], verts[1], verts[2]);
        ofPopMatrix();
    }

    gun.draw();
}

void Player::drawSprite() {
    ofSetColor(255, 255, 255);
    ofPushMatrix();
    ofMultMatrix(getMatrix());
    glm::vec3 c = getCenter();
    mySprite.draw(c.x - mySprite.getWidth() / 2, c.y - mySprite.getHeight() / 2);
    ofPopMatrix();
}

/*
* Calculates the center of a triangle using the centroid formula
*/
glm::vec3 Player::getCenter() {
    int x_sum = 0;
    int y_sum = 0;
    for (int i = 0; i < verts.size(); i++) {
        x_sum = x_sum + verts[i].x;
        y_sum = y_sum + verts[i].x;
    }
    return glm::vec3(x_sum / 3, y_sum / 3, 0);
}

// Integrator for simple trajectory physics
//
void Player::integrate() {

    // init current framerate (or you can use ofGetLastFrameTime())
    //
    float framerate = ofGetFrameRate();
    float dt = 1.0 / framerate;

    // linear motion
    //
    pos += (velocity * dt);
    glm::vec3 accel = acceleration;
    accel += (force * 1.0 / mass);
    velocity += accel * dt;
    velocity *= damping;

    // angular motion
    //
    rotation += (angularVelocity * dt);
    float a = angularAcceleration;
    a += (angularForce * 1.0 / mass);
    angularVelocity += a * dt;
    angularVelocity *= damping;

}

void Player::update(int health, glm::vec3 scale, bool sprite) {
    this->maxHealth = health;
    setScale(scale);
    hasSprite = sprite;
    integrate();
    force = glm::vec3(0);
    angularForce = 0;
    gun.update();
}

void Player::shoot(){
    float currentTime = ofGetElapsedTimeMillis();
    if (currentTime - lastShot > 300) {
        gun.spawnSprite(glm::vec3(getMatrix() * glm::vec4(verts[1], 1)), getHeading());
        lastShot = ofGetElapsedTimeMillis();
        int random = ofRandom(0, 2);
        if (random == 0) {
            shoot1.play();
        }
        else {
            shoot2.play();
        }
    }
}