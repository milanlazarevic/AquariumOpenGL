#pragma once
#include <GL/glew.h>

class Renderer {
public:
    static void drawRect(unsigned int shader, unsigned int VAO, float opacity = 1.0f);
    static void drawTexturedRect(unsigned int shader, unsigned int VAO, unsigned int texture, bool open = false);
    static void drawTexturedChest(unsigned int shader, unsigned int VAO, unsigned int texture, bool open);
    static void drawTexturedFish(unsigned int shader, unsigned int VAO, unsigned int texture, float uX, float uY, float flipped, float uS);
    static unsigned int createVAO(float* vertices, size_t size, int posSize, int texSize, int colSize);
};