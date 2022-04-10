/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#include "triangleShape.h"

/*
 Triangle Draw function
 Using Ofx Draw
 */
void TriangleShape::draw() {
    ofSetColor(getColor());
    ofFill();

    ofPushMatrix();
    ofMultMatrix(getMatrix());
    ofDrawTriangle(verts[0], verts[1], verts[2]);
    ofPopMatrix();
}

void TriangleShape::set(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    verts.clear();
    verts.push_back(v1);
    verts.push_back(v2);
    verts.push_back(v3);
}

/*
* Slightly Modified version of Professor Smith's code
* Commented so that I understand
* Adds up angles to check that they are all
*/
bool TriangleShape::inside(glm::vec3 p) {
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
* Calculates the center of a triangle using the centroid formula
*/
glm::vec3 TriangleShape::getCenter() {
    int x_sum = 0;
    int y_sum = 0;
    for (int i = 0; i < verts.size(); i++) {
        x_sum = x_sum + verts[i].x;
        y_sum = y_sum + verts[i].x;
    }
    return glm::vec3(x_sum / 3, y_sum / 3, 0);
}