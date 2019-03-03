#include "main.h"
#ifndef LIFEUP_H
#define LIFEUP_H



class Lifeup
{
public:
    Lifeup() {}
    Lifeup(float x, float y, color_t color);
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
VAO *object;

};

#endif // LIFEUP_H
