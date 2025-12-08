#pragma once

class Bubble {
public:
    Bubble(float speed);
    Bubble();
    float getX() const { return x; }
    float getY() const { return y; }
    void spawn(float x, float y);
    void update();
    void draw(unsigned int shader, unsigned int VAO, unsigned int texture);
    bool isActive() const { return active; }

private:
    float x, y;
    float speed;
    bool active;
};
