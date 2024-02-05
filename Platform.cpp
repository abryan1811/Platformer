#include "Platform.h"

// Constructor implementation
Platform::Platform(float x, float y, float width, float height) {
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    isSolid = true; // Assuming all platforms are solid by default
}

// Draw method implementation
void Platform::Draw() {
    DrawRectangleRec(rect, BLUE); // Draw the platform rectangle in blue
}

std::vector<Platform> Platform::GetAllPlatforms() 
{
    std::vector<Platform> platforms;

    platforms.emplace_back(0.5f * config::tileSize, 19 * config::tileSize, 8 * config::tileSize, 5 * config::tileSize);

    platforms.emplace_back(16.5f * config::tileSize, 13 * config::tileSize, 13 * config::tileSize, 11.5 * config::tileSize);

    platforms.emplace_back(29.0f * config::tileSize, 13 * config::tileSize, 1 * config::tileSize, config::tileSize);

    return platforms;
}