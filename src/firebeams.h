#include "main.h"
#ifndef FIREBEAMS_H
#define FIREBEAMS_H


class Firebeams
{
public:
    Firebeams(){};
    Firebeams(float x, float y, color_t color);
    glm::vec3 position;
    bool dir;
    bool reflect;
    float rotation;
    float width;
    float initial_x,initial_y;
    int flag, attack;
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
VAO *object2;
};

#endif // FIREBEAMS_H
