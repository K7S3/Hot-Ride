#include "main.h"
#ifndef SHIELD_POWERUP_H
#define SHIELD_POWERUP_H

class Shieldup
{
public:
    Shieldup() {}
    Shieldup(float x, float y, color_t color);
    glm::vec3 position;
    bool dir;
    bool reflect;
    int flag;
    float rotation;
    double speed;
    double xspeed;
    double yspeed;
    double radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
VAO *object1;
VAO *object2;
};

#endif // SHIELD_POWERUP_H
