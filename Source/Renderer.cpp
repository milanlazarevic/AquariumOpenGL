#include "../Header/Renderer.h"


void Renderer::drawRect(unsigned int shader, unsigned int VAO, float opacity) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "opacity"), opacity);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::drawTexturedRect(unsigned int shader, unsigned int VAO, unsigned int texture, bool open) {
    glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
    glUniform1f(glGetUniformLocation(shader, "uS"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uX"), 0.0f);
    glUniform1f(glGetUniformLocation(shader, "uY"), 0.0f);
    glUniform1f(glGetUniformLocation(shader, "flipped"), false);
    glUniform1f(glGetUniformLocation(shader, "open"), open);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::drawTexturedChest(unsigned int shader, unsigned int VAO, unsigned int texture, bool open)
{
    glUseProgram(shader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
    glUniform1f(glGetUniformLocation(shader, "uS"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uX"), 0.0f);
    glUniform1f(glGetUniformLocation(shader, "uY"), 0.0f);
    glUniform1f(glGetUniformLocation(shader, "flipped"), false);
    glUniform1f(glGetUniformLocation(shader, "open"), open);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::drawTexturedFish(unsigned int shader, unsigned int VAO, unsigned int texture, float uX, float uY, float flipped, float uS) {
    glUseProgram(shader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
    glUniform1f(glGetUniformLocation(shader, "uS"), uS);
    glUniform1f(glGetUniformLocation(shader, "uX"), uX);
    glUniform1f(glGetUniformLocation(shader, "uY"), uY);
    glUniform1f(glGetUniformLocation(shader, "flipped"), flipped);
    glUniform1f(glGetUniformLocation(shader, "open"), false);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

unsigned int Renderer::createVAO(float* vertices, size_t size, int posSize, int texSize, int colSize) {
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    if (colSize == 0) {
        int stride = (posSize + texSize) * sizeof(float);
        glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        if (texSize > 0) {
            glVertexAttribPointer(1, texSize, GL_FLOAT, GL_FALSE, stride, (void*)(posSize * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }
    else {
        int stride = (posSize + colSize) * sizeof(float);
        glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, colSize, GL_FLOAT, GL_FALSE, stride, (void*)(posSize * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    return VAO;
}