#include "../Header/FoodManager.h"
#include <cstdlib>
#include <iostream>

FoodManager::FoodManager(unsigned int shader, unsigned int VAO, unsigned int texture)
    : shader(shader), VAO(VAO), texture(texture) {}

void FoodManager::spawnFood(int count) {
    for (int i = 0; i < count; i++) {
        float x = -0.8f + static_cast<float>(rand()) / RAND_MAX * 1.6f;
        float y = 1.0f;
        float speed = -0.015f - static_cast<float>(rand()) / RAND_MAX * 0.02f;
        particles.push_back(FoodParticle(x, y, speed));
    }
}

void FoodManager::update() {
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const FoodParticle& p) { return !p.isActive() && p.isEaten(); }),
        particles.end()
    );

    for (auto& particle : particles) {
        particle.update();
    }
}

void FoodManager::draw() {
    for (auto& particle : particles) {
        particle.draw(shader, VAO, texture);
    }
}

void FoodManager::checkCollisions(float fishX, float fishY, float fishWidth, float fishHeight, std::function<void()> onEat) {
    for (auto& particle : particles) {
        if (particle.isActive() && !particle.isEaten()) {
            if (particle.checkCollision(fishX, fishY, fishWidth, fishHeight)) {
                particle.markAsEaten();
                if (onEat) onEat();
            }
        }
    }
}