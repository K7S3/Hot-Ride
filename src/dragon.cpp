#include "dragon.h"

#include "main.h"
#include "math.h"

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    lives = 2;
    radius = 0.5;
    speed = 3.0;
    xspeed = 0.04;
    yspeed = -0.015;
    flag=1;

    const int n = 9;
    const int reqd = n;
    GLfloat vertex_buffer_data[] = {

        0.25, 0.25,1.0,
        0.25, -0.25, 1.0,
        0.0, 0.0, 1.0,

        0.30, 0.30, 1.0,
        0.30, -0.30, 1.0,
        1.5, -0.8, 1.0
    };
    GLfloat vertex_buffer_data2[] = {
        0.0, 0.0, 1.0,
        -1.0, -1.5, 1.0,
        -2.5, -1.5, 1.0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6,vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_MAGNET,GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Dragon::tick() {
    if(flag==1&&this->position.y>=0.5)
     this->position.y-=0.01;
    else
        flag=0;
    if(flag==0&&this->position.y<=2.5)
        this->position.y+=0.01;
    else
        flag=1;
}
