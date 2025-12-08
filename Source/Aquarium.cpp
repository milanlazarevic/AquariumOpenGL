#include "../Header/Aquarium.h"



Aquarium::Aquarium(GLFWwindow* window, float wallWidth)
    : window(window),
    goldenFish(nullptr),
    clownFish(nullptr),
    foodManager(nullptr),
    grassTexture(0), grassRightTexture(0), sandTexture(0),
    chestClosedTexture(0), chestOpenTexture(0),
    goldenFishTexture(0), clownFishTexture(0),
    bubbleTexture(0), foodTexture(0),
    rectShader(0), textureShader(0),
    VAOrect(0), VAOrectRight(0), VAOrectBottom(0),
    VAOglassOverlay(0), VAOsandOverlay(0),
    VAOgrassOverlay(0), VAOgrass2Overlay(0),
    VAOchest(0), VAOclownFish(0), VAOgoldenFish(0),
    VAObubble(0), VAOclownBubble(0), VAOfoodParticle(0),
    isChestOpen(false),
    wallWidth(wallWidth)
{
}


void Aquarium::processTexture(unsigned& texture, const char* filepath) {
    texture = loadImageToTexture(filepath); // Učitavanje teksture
    if (texture == 0) {
        std::cout << "GRESKA: Tekstura nije ucitana!" << "\n";
        return;
    }

    std::cout << "Tekstura uspesno ucitana, ID: " << sandTexture << std::endl;
    glBindTexture(GL_TEXTURE_2D, texture); // Vezujemo se za teksturu kako bismo je podesili

    // Generisanje mipmapa - predefinisani različiti formati za lakše skaliranje po potrebi (npr. da postoji 32 x 32 verzija slike, ali i 16 x 16, 256 x 256...)
    glGenerateMipmap(GL_TEXTURE_2D);

    // Podešavanje strategija za wrap-ovanje - šta da radi kada se dimenzije teksture i poligona ne poklapaju
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S - tekseli po x-osi
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T - tekseli po y-osi

    // Podešavanje algoritma za smanjivanje i povećavanje rezolucije: nearest - bira najbliži piksel, linear - usrednjava okolne piksele
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Aquarium::loadTextures() {
    processTexture(sandTexture, "res/sand2.png");
    processTexture(grassTexture, "res/grass1.png");
    processTexture(grassRightTexture, "res/grass2.png");
    processTexture(chestClosedTexture, "res/chest_close.png");
    processTexture(chestOpenTexture, "res/chest_open.png");
    processTexture(goldenFishTexture, "res/golden_fish.png");
    processTexture(clownFishTexture, "res/clown_fish.png");
    processTexture(bubbleTexture, "res/bubble.png");
    processTexture(foodTexture, "res/food.png");
    processTexture(signatureTexture, "res/MilanLazarevicSV2-2022.png");
}

void::Aquarium::createShaders() {
    rectShader = createShader("Shaders/color.vert", "Shaders/color.frag");
    textureShader = createShader("Shaders/texture.vert", "Shaders/texture.frag");
}

void::Aquarium::createVAOs() {
    goldenFish = new Fish(0.0f, 0.0f, 0.01f, 1.0f, 0.7f, 1.0f, 0.0f, 0.5f,  goldenFishTexture);
    clownFish = new Fish(0.0f, 0.0f, 0.01f, 1.0f, -0.7f, -0.3f, 0.1f, 0.7f, clownFishTexture);

    float verticesRect[] = {
        -1.0f, 0.7f, 0.0f, 0.0f, 0.0f, // gornje levo teme
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // donje levo teme
        -1 + wallWidth, -1.0f, 0.0f, 0.0f, 0.0f, // donje desno teme
        -1 + wallWidth, 0.7f, 0.0f, 0.0f, 0.0f, // gornje desno teme
    };
    // right edge
    float verticesRectRight[] = {
         1.0f, 0.7f, 0.0f, 0.0f, 0.0f, // gornje levo teme
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // donje levo teme
         1 - wallWidth, -1.0f, 0.0f, 0.0f, 0.0f, // donje desno teme
         1 - wallWidth, 0.7f, 0.0f, 0.0f, 0.0f, // gornje desno teme
    };

    // bottom edge
    float verticesRectBottom[] = {
         -1.0f, -1.0f + wallWidth * 2, 0.0f, 0.0f, 0.0f, // gornje levo teme
         -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // donje levo teme
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // donje desno teme
         1.0f, -1.0f + wallWidth * 2, 0.0f, 0.0f, 0.0f, // gornje desno teme
    };

    // glass overlay
    float verticesGlassOverlay[] = {
         -1.0f, 0.7f, 1.0f, 1.0f, 1.0f, // gornje levo teme
         -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, // donje levo teme
         1.0f, -1.0f, 1.0f, 1.0f, 1.0f, // donje desno teme
         1.0f, 0.7f, 1.0f, 1.0f, 1.0f, // gornje desno teme
    };

    // sand
    float verticesSandOverlay[] = {
        // Pozicija      Tekstura
    -1.0f, -0.4f,   0.0f, 1.0f, // gornje levo
    -1.0f, -1.0f,   0.0f, 0.0f, // donje levo
     1.0f, -1.0f,   1.0f, 0.0f, // donje desno
     1.0f, -0.4f,   1.0f, 1.0f, // gornje desno
    };

    // grass left
    float verticesGrassOverlay[] = {
         -1.0f, -0.2f, 0.0f, 1.0f, // gornje levo teme
         -1.0f, -1.0f,0.0f, 0.0f, // donje levo teme
         -0.5f, -1.0f,1.0f, 0.0f, // donje desno teme
         -0.5f, -0.2f, 1.0f, 1.0f, // gornje desno teme
    };

    // grass right
    float verticesGrass2Overlay[] = {
        1.0f, -0.2f, 0.0f, 1.0f, // gornje levo teme
         1.0f, -0.8f,0.0f, 0.0f, // donje levo teme
         0.65f, -0.8f,1.0f, 0.0f, // donje desno teme
         0.65f, -0.2f, 1.0f, 1.0f, // gornje desno teme
    };

    // chest
    float verticesChest[] = {
        // Pozicija      Tekstura
     0.0f, -0.45f,   0.0f, 1.0f, // gornje levo
     0.0f, -0.85f,   0.0f, 0.0f, // donje levo
     0.4f, -0.85f,   1.0f, 0.0f, // donje desno
     0.4f, -0.45f,   1.0f, 1.0f, // gornje desno
    };

    // clown fish
    float verticesClownFish[] = {
        // Pozicija      Tekstura
     clownFish->getMinX(), clownFish->getMaxY(),   0.0f, 1.0f, // gornje levo
     clownFish->getMinX(), clownFish->getMinY(),   0.0f, 0.0f, // donje levo
     clownFish->getMaxX(), clownFish->getMinY(),   1.0f, 0.0f, // donje desno
     clownFish->getMaxX(), clownFish->getMaxY(),   1.0f, 1.0f, // gornje desno
    };

    // golden fish
    float verticesGoldenFish[] = {
        // Pozicija      Tekstura
      goldenFish->getMinX(), goldenFish->getMaxY(),   0.0f, 1.0f, // gornje levo
      goldenFish->getMinX(), goldenFish->getMinY(),   0.0f, 0.0f, // donje levo
      goldenFish->getMaxX(), goldenFish->getMinY(),   1.0f, 0.0f, // donje desno
      goldenFish->getMaxX(), goldenFish->getMaxY(),   1.0f, 1.0f, // gornje desno
    };

    float verticesBubble[] = {
        // Pozicija      Tekstura
      0.0f, 0.04f,   0.0f, 1.0f, // gornje levo
      0.0f, -0.05f,   0.0f, 0.0f, // donje levo
      0.05f, -0.05f,   1.0f, 0.0f, // donje desno
      0.05f, 0.04f,   1.0f, 1.0f, // gornje desno
    };

    float verticesSignature[] = {
        // Pozicija      Tekstura
      0.65f, 1.0f,   0.0f, 1.0f, // gornje levo
      0.65f, 0.7f,   0.0f, 0.0f, // donje levo
      1.0f, 0.7f,   1.0f, 0.0f, // donje desno
      1.0f, 1.0f,   1.0f, 1.0f, // gornje desno
    };


    VAOrect = Renderer::createVAO(verticesRect, sizeof(verticesRect), 2,0,3);
    VAOrectRight = Renderer::createVAO(verticesRectRight, sizeof(verticesRectRight), 2, 0, 3);
    VAOrectBottom = Renderer::createVAO(verticesRectBottom, sizeof(verticesRectBottom), 2, 0, 3);
    VAOglassOverlay = Renderer::createVAO(verticesGlassOverlay, sizeof(verticesGlassOverlay), 2, 0, 3);
    VAOsandOverlay = Renderer::createVAO(verticesSandOverlay, sizeof(verticesSandOverlay), 2, 2, 0);
    VAOgrassOverlay = Renderer::createVAO(verticesGrassOverlay, sizeof(verticesGrassOverlay), 2, 2, 0);
    VAOgrass2Overlay = Renderer::createVAO(verticesGrass2Overlay, sizeof(verticesGrass2Overlay), 2, 2, 0);
    VAOchest = Renderer::createVAO(verticesChest, sizeof(verticesChest), 2, 2, 0);
    VAOclownFish = Renderer::createVAO(verticesClownFish, sizeof(verticesClownFish), 2, 2, 0);
    VAOgoldenFish = Renderer::createVAO(verticesGoldenFish, sizeof(verticesGoldenFish), 2, 2, 0);
    VAObubble = Renderer::createVAO(verticesBubble, sizeof(verticesBubble), 2, 2, 0);
    VAOclownBubble = Renderer::createVAO(verticesBubble, sizeof(verticesBubble), 2, 2, 0);
    VAOfoodParticle = Renderer::createVAO(verticesBubble, sizeof(verticesBubble), 2, 2, 0);
    VAOsignature = Renderer::createVAO(verticesSignature, sizeof(verticesSignature), 2, 2, 0);
}

void Aquarium::processInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        isChestOpen = !isChestOpen;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        spawnBubbles(goldenBubbles, !goldenFish->isFlipped() ? 0.7f + goldenFish->getX() : 1.0f + goldenFish->getX(), 0.25f*goldenFish->getScale() + goldenFish->getY());
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        spawnBubbles(clownBubbles, clownFish->isFlipped() ? -0.34f + clownFish->getX() : -0.7f + clownFish->getX(), 0.3f*clownFish->getScale() + clownFish->getY());
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        foodManager->spawnFood();
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Aquarium::spawnBubbles(Bubble(&bubbles)[3], float fishX, float fishY) {
    for (Bubble& bubble : bubbles) {
        if (!bubble.isActive()) {
            bubble.spawn(fishX, fishY);
        }
    }
}

bool Aquarium::initialize() {
    loadTextures();
    createShaders();
    createVAOs();
    foodManager = new FoodManager(textureShader, VAOfoodParticle, foodTexture);
    return true;
}

void Aquarium::run() {
    Renderer::drawTexturedRect(textureShader, VAOsignature, signatureTexture);
    Renderer::drawTexturedRect(textureShader, VAOsandOverlay, sandTexture);
    Renderer::drawTexturedRect(textureShader, VAOgrassOverlay, grassTexture);
    Renderer::drawTexturedRect(textureShader, VAOgrass2Overlay, grassRightTexture);
    Renderer::drawTexturedChest(textureShader, VAOchest, (isChestOpen) ? chestOpenTexture : chestClosedTexture, isChestOpen);
    Renderer::drawTexturedFish(textureShader, VAOclownFish, clownFishTexture, clownFish->getX(), clownFish->getY(), clownFish->isFlipped(), clownFish->getScale());
    Renderer::drawTexturedFish(textureShader, VAOgoldenFish, goldenFishTexture, goldenFish->getX(), goldenFish->getY(), goldenFish->isFlipped(), goldenFish->getScale());
    Renderer::drawRect(rectShader, VAOrect);
    Renderer::drawRect(rectShader, VAOrectRight);
    Renderer::drawRect(rectShader, VAOrectBottom);
    Renderer::drawRect(rectShader, VAOglassOverlay, 0.2f);
    //drawing bubbles
    for (int i = 0; i < 3; i++) {
        if (goldenBubbles[i].isActive()) {
            goldenBubbles[i].update();
            goldenBubbles[i].draw(textureShader, VAObubble, bubbleTexture);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (clownBubbles[i].isActive()) {
            clownBubbles[i].update();
            clownBubbles[i].draw(textureShader, VAObubble, bubbleTexture);
        }
    }
    handleMovement();
    goldenFish->checkBoundaries(0.7f, -0.9f, -1.0f, 1.0f);
    clownFish->checkBoundaries(0.7f, -0.9f, -1.0f, 1.0f);
    foodManager->draw();
    foodManager->update();
    foodManager->checkCollisions(goldenFish->getMinX() + goldenFish->getX(), 
        goldenFish->getMaxY() * goldenFish->getScale() + goldenFish->getY(), 
        goldenFish->getWidth(), (goldenFish->getMaxY() - goldenFish->getMinY()) * goldenFish->getScale(), std::bind(&Fish::eat, goldenFish));

    foodManager->checkCollisions(clownFish->getMinX() + clownFish->getX(),
        clownFish->getMaxY() * clownFish->getScale() + clownFish->getY(),
        clownFish->getWidth(), (clownFish->getMaxY() - clownFish->getMinY()) * clownFish->getScale(), std::bind(&Fish::eat, clownFish));
}

void Aquarium::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Aquarium* aquarium = static_cast<Aquarium*>(glfwGetWindowUserPointer(window));
    if (aquarium)
        aquarium->processInput(window, key, scancode, action, mods);
}

void Aquarium::handleMovement() {
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        goldenFish->moveLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        goldenFish->moveRight();
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        goldenFish->moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        goldenFish->moveDown();
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        clownFish->moveLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        clownFish->moveRight();
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        clownFish->moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        clownFish->moveDown();
    }
}