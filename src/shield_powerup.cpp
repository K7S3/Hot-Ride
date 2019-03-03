#include "shield_powerup.h"
#include "main.h"
#include "math.h"
#include "stdlib.h"

Shieldup::Shieldup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = 0.4;
    speed = 5.0;
    flag=1;

    GLfloat vertex_buffer_data1[] = {
        -0.4f, 0.2f, 0.0f,
        0.4, 0.2f, 0.0f,
        0.0f, -0.4f, 0.0f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 3 ,vertex_buffer_data1, color, GL_FILL);

    const int n = 40;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data2[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    //GLfloat vertex_buffer_data[12345];

    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data2[cur++] = 0.0;
        vertex_buffer_data2[cur++] = 0.0;
        vertex_buffer_data2[cur++] = -1.0f;

        //Point with lower angle
        vertex_buffer_data2[cur++] = radius * cos(angle);
        vertex_buffer_data2[cur++] = radius * sin(angle);
        vertex_buffer_data2[cur++] = -1.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data2[cur++] = radius * cos(angle);
        vertex_buffer_data2[cur++] = radius * sin(angle);
        vertex_buffer_data2[cur++] = -1.0f;
    }


    this->object2 = create3DObject(GL_TRIANGLES, 3 * n, vertex_buffer_data2, COLOR_WHITE, GL_FILL);
}

void Shieldup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Shieldup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Shieldup::tick(){
    this->rotation += speed;
    this->position.x -=0.02;
    if(flag==1&&this->position.y>=-0.5)
     this->position.y-=0.01;
    else
        flag=0;
    if(flag==0&&this->position.y<=2.5)
        this->position.y+=0.01;
    else
        flag=1;
}
