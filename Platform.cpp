#include "Platform.h"
#include <iostream>

Platform::Platform()
{
    mapPosition = {0.0f, 0.0f};
}

//Sets up textures to overlap main background. 
void Platform::InitializeTextures()
{
    upDownPlatformMap = LoadTexture("Assets/upDownPlatform.png");
    // Add checks here
    if (upDownPlatformMap.id == 0)
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

// Constructor implementation
Platform::Platform(float x, float y, float width, float height)
{
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    isSolid = true;
}

// Draw method implementation
void Platform::Draw()
{
    DrawRectangleRec(rect, BLUE); // Draw the platform rectangle in blue
}

void Platform::DrawMovingTexture() {
    // Draw the texture scaled to cover the screen, moving vertically.
    DrawTextureEx(upDownPlatformMap, mapPosition, 0.0f, 1.0f, WHITE);
}

std::vector<Platform> Platform::GetAllPlatforms()
{
    std::vector<Platform> platforms;
    // Create the static platforms rectangles
    platforms.emplace_back(0.5f * config::tileSize, 19 * config::tileSize, 8 * config::tileSize, 5 * config::tileSize);

    platforms.emplace_back(16.5f * config::tileSize, 13 * config::tileSize, 13 * config::tileSize, 11.5 * config::tileSize);

    platforms.emplace_back(29.0f * config::tileSize, 13 * config::tileSize, 1 * config::tileSize, config::tileSize);

    return platforms;
}

std::vector<Platform> Platform::GetUpwardsMovingPlatforms()
{
    std::vector<Platform> upwardMovingPlatforms;
    // Create a moving platform with specific parameters for size and locations. 
    Platform movingPlatform(10.3f * config::tileSize, 19.6f * config::tileSize, 3 * config::tileSize, 0.5f * config::tileSize);
    movingPlatform.movesUpAndDown = true;
    movingPlatform.minY = 19 * config::tileSize - (7 * config::tileSize); // Move up 2 tiles
    movingPlatform.maxY = 19 * config::tileSize;                          // Original position
    movingPlatform.movingSpeed = 50;                                      // Speed of movement
    movingPlatform.movingUp = true;                                       // Start moving up

    upwardMovingPlatforms.push_back(movingPlatform);
    return upwardMovingPlatforms;
}

void Platform::UpdateDownToUpMovement(float deltaTime)
{
    if (!movesUpAndDown)
        return;

    float movement = movingSpeed * deltaTime * (movingUp ? -1.0f : 1.0f);
    rect.y += movement; // moves the collision rectangle as well

     mapPosition.y += movement;

    // Reverse direction if necessary
    if (movingUp && rect.y <= minY)
    {
        movingUp = false;
    }
    else if (!movingUp && rect.y >= maxY)
    {
        movingUp = true;
    }
}


