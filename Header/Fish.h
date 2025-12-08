#pragma once
#include <GL/glew.h>

class Fish {
public:
    Fish(float x, float y, float speed, float scale, float minX, float maxX, float minY, float maxY, unsigned int texture);

    float getX() const { return x; }
    float getY() const { return y; }
    float getScale() const { return scale; }
    bool isFlipped() const { return flipped; }
    float getMinX() const { return minX; }
    float getMaxX() const { return maxX; }
    float getMinY() const { return minY; }
    float getMaxY() const { return maxY; }
    float getWidth() const { return maxX - minX; }
    float getHeight() const { return maxY - minY; }
    void setTexture(unsigned int texture) { texture = texture; }
    void grow();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void checkBoundaries(float topBound, float bottomBound, float leftBound, float rightBound);
    void eat(); // Povećava skalu
    void draw(unsigned int shader, unsigned int VAO, unsigned int texture);

private:
    float x, y;
    float scale;
    float speed;
    bool flipped;
    float minX, maxX, minY, maxY;
    unsigned int texture;
};