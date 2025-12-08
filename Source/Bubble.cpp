#include "../Header/Bubble.h"
#include <GL/glew.h>

Bubble::Bubble(float speed) : x(0.0f), y(0.0f), speed(speed), active(false) {}
Bubble::Bubble() : x(0.0f), y(0.0f), speed(0.5f), active(false) {}

void Bubble::spawn(float x, float y) {
    this->x = x;
    this->y = y;
    this->active = true;
}

void Bubble::update() {
    if (active) {
        y += speed;
        if (y > 0.7f) {
            active = false;
        }
    }
}

void Bubble::draw(unsigned int shader, unsigned int VAO, unsigned int texture) {
    if (!active) return;

    glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
    glUniform1f(glGetUniformLocation(shader, "uS"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uX"), x);
    glUniform1f(glGetUniformLocation(shader, "uY"), y);
    glUniform1f(glGetUniformLocation(shader, "flipped"), false);
    glUniform1f(glGetUniformLocation(shader, "open"), false);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
