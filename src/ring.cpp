#include "ring.h"
#include "main.h"
#include "math.h"
#include "stdlib.h"

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = 1.0;
    speed = 3.0;
    const int n = 360;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    //GLfloat vertex_buffer_data[12345];

    for (int i = 0; i < n; i++)
    {

        //Origin
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = -radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = -radius * sin(angle);
        vertex_buffer_data[cur++] = 0.0f;

}
    this->object = create3DObject(GL_TRIANGLES, 3*n/2, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    GLfloat vertex_buffer_data2[reqd] = {};
    this->radius1 = 0.9;

    angle = 0;
    cur = 0;


    for (int i = 0; i < n; i++)
    {

        //Origin
        vertex_buffer_data2[cur++] = 0.0;
        vertex_buffer_data2[cur++] = 0.0;
        vertex_buffer_data2[cur++] = 0.1f;

        //Point with lower angle
        vertex_buffer_data2[cur++] = radius1 * cos(angle);
        vertex_buffer_data2[cur++] = -radius1 * sin(angle);
        vertex_buffer_data2[cur++] = 0.1f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data2[cur++] = radius1 * cos(angle);
        vertex_buffer_data2[cur++] = -radius1 * sin(angle);
        vertex_buffer_data2[cur++] = 0.1f;

}
    this->object2 = create3DObject(GL_TRIANGLES, 3*n/2, vertex_buffer_data2, COLOR_WHITE, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Ring::bounding_box() {
    bounding_box_t box;
    box.x = this->position.x;
    box.y = this->position.y;
    box.height = 2*this->radius;
    box.width = 2*this->radius;
    return box;
}
void Ring::tick(){
//     this->rotation += speed;
}
