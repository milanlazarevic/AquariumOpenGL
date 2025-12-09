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

    Fish* goldenFish;
    Fish* clownFish;

    FoodManager* foodManager;

    Bubble goldenBubbles[3] = {
            Bubble(0.01f),
            Bubble(0.02f),
            Bubble(0.03f)
    };
    Bubble clownBubbles[3] = {
            Bubble(0.01f),
            Bubble(0.02f),
            Bubble(0.03f)
    };

    unsigned int grassTexture, grassRightTexture, sandTexture;
    unsigned int chestClosedTexture, chestOpenTexture;
    unsigned int goldenFishTexture, clownFishTexture;
    unsigned int bubbleTexture, foodTexture;
    unsigned int signatureTexture;

    unsigned int rectShader, textureShader;

    unsigned int VAOrect, VAOrectRight, VAOrectBottom;
    unsigned int VAOglassOverlay, VAOsandOverlay;
    unsigned int VAOgrassOverlay, VAOgrass2Overlay;
    unsigned int VAOchest, VAOclownFish, VAOgoldenFish;
    unsigned int VAObubble,VAOclownBubble, VAOfoodParticle;
    unsigned int VAOsignature;

    bool isChestOpen;

    float wallWidth;
};
