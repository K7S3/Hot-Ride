#include "main.h"
#ifndef BOOMERANG_H
#define BOOMERANG_H





class Boomerang
{
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
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
    void tick2();
    void tick3();
private:
VAO *object;
};

#endif // BOOMERANG_H
