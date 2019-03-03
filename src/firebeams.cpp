#include "firebeams.h"
#include "main.h"
#include "math.h"

Firebeams::Firebeams(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->initial_x = x;
    this->initial_y = y;
    this->rotation = 0;
    radius = 0.20;
    speed = 0.01;
    width = 0.40;

    flag = 1;
    attack = 0;
//    xspeed = 0.03;
//    yspeed = -0.01;

    const int n = 360;
    const int reqd = n * 9*2*2;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    //GLfloat vertex_buffer_data[12345];


    for (int i = 0; i < n; i++)
    {
        //Origin
        vertex_buffer_data[cur++] = -4.0;
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = -4+radius * cos(angle);
        vertex_buffer_data[cur++] = 0+radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data[cur++] = -4+radius * cos(angle);
        vertex_buffer_data[cur++] = 0+radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;
    }



    for (int i = n; i < 2*n; i++)
    {
        //Origin
        vertex_buffer_data[cur++] = 4.0f;
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = 4+radius * cos(angle);
        vertex_buffer_data[cur++] = 0+radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data[cur++] = 4+radius * cos(angle);
        vertex_buffer_data[cur++] = 0+radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;
    }
GLfloat vertex_buffer_data2[reqd] = {};
cur = 0;
    vertex_buffer_data2[cur++] = -4.0f;
    vertex_buffer_data2[cur++] = 0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    vertex_buffer_data2[cur++] = -4.0f;
    vertex_buffer_data2[cur++] = -0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    vertex_buffer_data2[cur++] = 4.0f;
    vertex_buffer_data2[cur++] = -0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    vertex_buffer_data2[cur++] = 4.0f;
    vertex_buffer_data2[cur++] = 0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    vertex_buffer_data2[cur++] = -4.0f;
    vertex_buffer_data2[cur++] = 0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    vertex_buffer_data2[cur++] = 4.0f;
    vertex_buffer_data2[cur++] = -0.1f;
    vertex_buffer_data2[cur++] = -1.0f;

    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*6, vertex_buffer_data2, COLOR_MAGNET, GL_FILL);
}

void Firebeams::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->attack==1)
    draw3DObject(this->object2);
}

void Firebeams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Firebeams::bounding_box() {
    bounding_box_t box;
    box.x = this->position.x;
    box.y = this->position.y;
    box.height = 2*this->radius;
    box.width = 6+4*this->radius;
    return box;
}
void Firebeams::tick() {
//     this->rotation += speed;
    this->position.x += speed;
    if(flag==1&&this->position.y>=initial_y+0.5)
     this->position.y-=0.01;
    else
        flag=0;
    if(flag==0&&this->position.y<=initial_y+1.5)
        this->position.y+=0.01;
    else
        flag=1;
}
