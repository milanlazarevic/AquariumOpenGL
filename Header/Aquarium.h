#pragma once
//#include <GLFW/glfw3.h>
#include <vector>
#include "Fish.h"
#include "FoodManager.h"
#include "Bubble.h"
#include "Util.h"
#include <iostream>
#include "Renderer.h"

class Aquarium {
public:
    Aquarium(GLFWwindow* window, float wallWidth);
    //~Aquarium();

    bool initialize();
    void run();
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    void loadTextures();
    void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void processTexture(unsigned& texture, const char* filepath);
    void createShaders();
    void createVAOs();
    void spawnBubbles(Bubble(&bubbles)[3], float fishX, float fishY);
    void update();
    void render();
    void handleMovement();


    GLFWwindow* window;

    // Ribe
    Fish* goldenFish;
    Fish* clownFish;

    // Food sistem
    FoodManager* foodManager;

    // Bubbles
    Bubble goldenBubbles[3] = {
            Bubble(0.001f),
            Bubble(0.002f),
            Bubble(0.003f)
    };
    Bubble clownBubbles[3] = {
            Bubble(0.001f),
            Bubble(0.002f),
            Bubble(0.003f)
    };

    // Teksture
    unsigned int grassTexture, grassRightTexture, sandTexture;
    unsigned int chestClosedTexture, chestOpenTexture;
    unsigned int goldenFishTexture, clownFishTexture;
    unsigned int bubbleTexture, foodTexture;

    // Šejderi
    unsigned int rectShader, textureShader;

    // VAO-ovi
    unsigned int VAOrect, VAOrectRight, VAOrectBottom;
    unsigned int VAOglassOverlay, VAOsandOverlay;
    unsigned int VAOgrassOverlay, VAOgrass2Overlay;
    unsigned int VAOchest, VAOclownFish, VAOgoldenFish;
    unsigned int VAObubble,VAOclownBubble, VAOfoodParticle;

    // Stanje
    bool isChestOpen;

    float wallWidth;
};
