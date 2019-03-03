#include "main.h"
#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    color_t color;
    bool dir;
    bool reflect;
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
    void speedtick();
    bounding_box_t bounding_box();
private:
VAO *object;
VAO *object2;
};

#endif // PLAYER_H
