#include "../Header/FoodParticle.h"
#include <GL/glew.h>


const float FOOD_WIDTH = 0.05f;
const float FOOD_HEIGHT = 0.09f;

FoodParticle::FoodParticle(float x, float y, float speed)
    : x(x), y(y), speed(speed), eaten(false), active(true) {}

void FoodParticle::update() {
    if (active && !eaten) {
        y += (y < -0.8f) ? 0.0f : speed;
    }
}

void FoodParticle::draw(unsigned int shader, unsigned int VAO, unsigned int texture) {
    if (!active || eaten) return;

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

bool FoodParticle::checkCollision(float fishX, float fishY, float fishWidth, float fishHeight) {
    return (fishX < x + FOOD_WIDTH &&
        fishX + fishWidth > x &&
        fishY > y - FOOD_HEIGHT &&
        fishY - fishHeight < y);
}
