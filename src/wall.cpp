#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->cord_x = 2;
    const int n = 360;
    const int reqd = n * 9*3;
    GLfloat vertex_buffer_data[reqd] = {};
    int cur = 0;
    //GLfloat vertex_buffer_data[12345];

    for (int i = 0; i < n; i+=3)
    {
        int x = 2 + rand()%1;
//        vertex_buffer_data[cur++] = i-1.5;
//        vertex_buffer_data[cur++] = 2.5;
//        vertex_buffer_data[cur++] = -3;

//        vertex_buffer_data[cur++] = i-2.5;
//        vertex_buffer_data[cur++] = 2.5;
//        vertex_buffer_data[cur++] = -3;


//        vertex_buffer_data[cur++] = i-1.5;
//        vertex_buffer_data[cur++] = 3.5;
//        vertex_buffer_data[cur++] = -3;

        vertex_buffer_data[cur++] = i-0.5;
        vertex_buffer_data[cur++] = 2.5-2+x;
        vertex_buffer_data[cur++] = -3;

        vertex_buffer_data[cur++] = i+1.5;
        vertex_buffer_data[cur++] = 2.5-2+x;
        vertex_buffer_data[cur++] = -3;


        vertex_buffer_data[cur++] = i+0.5;
        vertex_buffer_data[cur++] = 3.5-2+x;
        vertex_buffer_data[cur++] = -3;

        vertex_buffer_data[cur++] = i-2;
        vertex_buffer_data[cur++] = 1;
        vertex_buffer_data[cur++] = -2;

        vertex_buffer_data[cur++] = i;
        vertex_buffer_data[cur++] = 1;
        vertex_buffer_data[cur++] = -2;


        vertex_buffer_data[cur++] = i;
        vertex_buffer_data[cur++] = 1+x;
        vertex_buffer_data[cur++] = -2;


        vertex_buffer_data[cur++] = i-2;
        vertex_buffer_data[cur++] = 1+x;
        vertex_buffer_data[cur++] = -2;

        vertex_buffer_data[cur++] = i;
        vertex_buffer_data[cur++] = 1+x;
        vertex_buffer_data[cur++] = -2;

        vertex_buffer_data[cur++] = i-2;
        vertex_buffer_data[cur++] = 1;
        vertex_buffer_data[cur++] = -2;



    }

this->object = create3DObject(GL_TRIANGLES, 3*n*3, vertex_buffer_data, color, GL_FILL);
}
void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
     glm::mat4 translate = glm::translate(glm::vec3(0, -0.25, 0)); // glTranslatef
     glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
     rotate = rotate * glm::translate(glm::vec3(0, -1.0, 0));
     Matrices.model *= (translate * rotate);
     glm::mat4 MVP = VP * Matrices.model;
     glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
//     glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

