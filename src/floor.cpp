#include "floor.h"
#include "main.h"

Floor::Floor(float x, float y, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->cord_x = 360;
    static const GLfloat vertex_buffer_data[] = {
        -cord_x, -4, 0, // vertex 1
        cord_x, -4, 0,  // vertex 2
        cord_x, 0, 0,   // vertex 3

        cord_x, 0, 0,  // vertex 3
        -cord_x, 0, 0, // vertex 4
        -cord_x, -4, 0 // vertex 1
    };

this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}
void Floor::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Floor::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
bounding_box_t Floor::bounding_box() {
    bounding_box_t box;
    box.height = 0;
    box.width = 720;
    box.x = this->position.x;
    box.y = this->position.y;
    return box;
}
