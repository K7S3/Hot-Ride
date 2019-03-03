#include "main.h"
#ifndef DRAGON_H
#define DRAGON_H



class Dragon
{
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    color_t color;
    bool dir;
    bool reflect;
    int flag;
    float rotation;
    double xspeed;
    double yspeed;
    double radius;
    double score;
    double speed;
    int jump;
    int lives;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    bounding_box_t bounding_box();
private:
VAO *object;
VAO *object2;
};




#endif // DRAGON_H
