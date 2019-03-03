#include "main.h"
#ifndef RING_H
#define RING_H

class Ring
{
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    bool dir;
    bool reflect;
    float rotation;
    double speed;
    double xspeed;
    double yspeed;
    double radius, radius1;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
VAO *object;
VAO *object2;
};

#endif // RING_H
