#include "water_balloon.h"
#include "main.h"
#include "math.h"
#include "stdlib.h"

Water_balloon::Water_balloon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->initial_y = y;
    xspeed = 0.00;
    yspeed = 0.06;
    radius = 0.1;
    speed = 3.0;
    const int n = 20;
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
        vertex_buffer_data[cur++] = 2.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = radius * sin(angle);
        vertex_buffer_data[cur++] = 2.0f;

        //Point with higher angle
        angle += diff;
        vertex_buffer_data[cur++] = radius * cos(angle);
        vertex_buffer_data[cur++] = radius * sin(angle);
        vertex_buffer_data[cur++] = 2.0f;

}

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Water_balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water_balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Water_balloon::bounding_box() {
    bounding_box_t box;
    box.x = this->position.x;
    box.y = this->position.y;
    box.height = 2*this->radius;
    box.width = 2*this->radius;
    return box;
}
void Water_balloon::tick(){
//     this->rotation += speed;
     this->position.x +=0.08;
     this->position.y += yspeed;
     yspeed -= 0.002;
//    if(this->position.y>=initial_y + 2)
//        yspeed = -0.01;
}
