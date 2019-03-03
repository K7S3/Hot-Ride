#include "main.h"
#ifndef SCORE_H
#define SCORE_H

class Score {
public:
    Score() {}
    Score(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y);
    void tick1();
    void tick2();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;

};


#endif // SCORE_H
