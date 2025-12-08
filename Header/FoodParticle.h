#pragma once
class FoodParticle
{
public:
    FoodParticle(float x, float y, float speed);

    float getX() const { return x; }
    float getY() const { return y; }
    bool isActive() const { return active; }
    bool isEaten() const { return eaten; }

    void update();
    void markAsEaten() { eaten = true; active = false; }
    void draw(unsigned int shader, unsigned int VAO, unsigned int texture);

    bool checkCollision(float fishX, float fishY, float fishWidth, float fishHeight);
private:
    float x, y;
    float speed;
    bool eaten;
    bool active;
};

