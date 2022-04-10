/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#pragma once
#include "ofMain.h"

/*
* Shape class for Basic shapes
*/
class Shape {
public:
    Shape() {}
    virtual void draw() {

        // draw a box by defaultd if not overridden
        //
        ofPushMatrix();
        ofMultMatrix(getMatrix());
        ofDrawBox(defaultSize);
        ofPopMatrix();
    }
    virtual bool inside(glm::vec3 p) {
        return false;
    }
    virtual glm::vec3 getCenter() {
        return glm::vec3(0, 0, 0);
    };
    //Sets the position of the shape
    void setPos(glm::vec3 pos) {
        this->pos = pos;
    }

    //Gets the position of the shape
    glm::vec3 getPos() {
        return this->pos;
    }

    /*
    * Gets the translation matrix of the shape
    */
    glm::mat4 getTranslationMatrix() {
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
        return trans;
    }
    //Sets the current rotation in degrees
    void setRotation(float degrees) {
        this->rotation = degrees;
    }

    //Gets the rotation of the shape
    float getRotation() {
        return this->rotation;
    }

    //Gets the rotation matrix of the shape
    glm::mat4 getRotationMatrix() {
        return glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
    }

    //Sets the scale
    void setScale(glm::vec3 scale) {
        this->scale = scale;
    }

    //Gets the current scale
    glm::vec3 getScale() {
        return this->scale;
    }

    //Gets the current color
    ofColor getColor() {
        return color;
    }

    //Sets the current default color
    void setColor(ofColor color) {
        this->color = color;
    }

    /*
    * Creates the transformation matrix by multiplying the transformation matrices
    * Returns the transformation matrix
    */
    glm::mat4 getMatrix() {
        glm::mat4 rot = getRotationMatrix();
        glm::mat4 sc = glm::scale(scale);
        glm::mat4 trans = getTranslationMatrix();
        return trans * sc * rot;
    }

    vector<glm::vec3> verts;

private:
    glm::vec3 pos;

    //Channels
    float rotation = 0.0; // degrees
    ofColor color = ofColor::black;
    glm::vec3 scale = glm::vec3(1, 1, 1);
    float defaultSize = 20.0;


};