#include "main.h"
#ifndef COINS_H
#define COINS_H


class Coins
{
public:
    Coins() {}
    Coins(float x, float y, color_t color);
    glm::vec3 position;
    bool dir;
    bool reflect;
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
VAO *object;
};

#endif // COINS_H
