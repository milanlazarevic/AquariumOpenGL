#pragma once
#include <vector>
#include "FoodParticle.h"
#include <functional>


class FoodManager {
public:
    FoodManager(unsigned int shader, unsigned int VAO, unsigned int texture);

    void spawnFood(int count = 3);
    void update();
    void draw();
    void checkCollisions(float fishX, float fishY, float fishWidth, float fishHeight, std::function<void()> onEat);

private:
    std::vector<FoodParticle> particles;
    unsigned int shader;
    unsigned int VAO;
    unsigned int texture;
};