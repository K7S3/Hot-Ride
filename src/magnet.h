#include "main.h"
#ifndef MAGNET_H
#define MAGNET_H

class Magnet
{
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    color_t color;
    bool dir;
    bool reflect;
    float rotation;
    double xspeed;
    double yspeed;
    double radius;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick1();

private:
VAO *object;
};

#endif // MAGNET_H
