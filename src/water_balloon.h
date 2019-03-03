#include "main.h"
#ifndef WATER_BALLOON_H
#define WATER_BALLOON_H


class Water_balloon
{
public:
    Water_balloon() {}
    Water_balloon(float x, float y, color_t color);
    glm::vec3 position;
    color_t color;
    float rotation;
    double xspeed;
    double initial_y;
    double yspeed;
    double radius;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
VAO *object;

};

#endif // WATER_BALLOON_H
