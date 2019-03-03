#include "lifeup.h"
#include "main.h"
#include "math.h"
#include "stdlib.h"

Lifeup::Lifeup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = 0.4;
    speed = 5.0;
    flag=1;

    GLfloat vertex_buffer_data1[] = {

        -0.4f, 0.2f, 0.0f,
        0.4, 0.2f, 0.0f,
        0.0f, -0.4f, 0.0f,

         -0.2f, 0.4f, 0.0f,
        -0.4f, 0.2f, 0.0f,
         0.1f, 0.2f, 0.0f,

        0.2f, 0.4f, 0.0f,
        -0.1f, 0.2f, 0.0f,
        0.4f, 0.2f, 0.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 9 ,vertex_buffer_data1, color, GL_FILL);

}

void Lifeup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Lifeup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Lifeup::tick(){
//    this->rotation += speed;
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
