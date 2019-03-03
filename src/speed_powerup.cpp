#include "speed_powerup.h"

#include "main.h"
#include "math.h"
#include "stdlib.h"

Speedup::Speedup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = 0.25;
    speed = 3.0;
    flag=1;
    GLfloat vertex_buffer_data1[] = {
        0.0f, 0.25f, 1.0f,
        0.25f, 0.0f, 1.0f,
        0.0f, -0.25f, 1.0f
    };
    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;
    }
    this->object1 = create3DObject(GL_TRIANGLES, 3 ,vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n ,vertex_buffer_data, COLOR_CYAN, GL_FILL);
}

void Speedup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
}

void Speedup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Speedup::bounding_box() {
    bounding_box_t box;
    box.x = this->position.x;
    box.y = this->position.y;
    box.height = 2*this->radius;
    box.width = 2*this->radius;
    return box;
}
void Speedup::tick(){

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
