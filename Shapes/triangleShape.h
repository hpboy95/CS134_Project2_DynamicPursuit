/*
* Hezekiah Valdez
* CS134 2/21/2022
*/

#pragma once
#include "shape.h"
class TriangleShape : public Shape {
public:
    TriangleShape() {
        // default data
        set(glm::vec3(20, 20, 0), glm::vec3(0, -40, 0), glm::vec3(-20, 20, 0));
    }
    TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
    }

    void set(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    void draw();
    glm::vec3 getCenter();
    bool inside(glm::vec3 p);
};