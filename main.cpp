#include "main.h"

// Number of tiles horizontally and vertically
int numTilesX = 200;
int numTilesY = 24;

// Window Width in tiles
int windowTilesX = 25;

// Calculate the window width and height
int windowWidth = windowTilesX * config::tileSize;
int windowHeight = numTilesY * config::tileSize;
char windowTitle[]{"Platformer"};

// Variables for the image
Texture2D worldMap;
Vector2 mapPosition;
Platform platform;

int main(int argc, char const *argv[])
{
    InitWindow(windowWidth, windowHeight, windowTitle);

    SetTargetFPS(60);

    worldMap = LoadTexture("Assets/levelplatformer.png");
    mapPosition = {0.0, 0.0};

    platform.InitializeTextures();

    Character player;

    std::vector<Platform> platforms = Platform::GetAllPlatforms();

    std::vector<Platform> movingPlatforms = Platform::GetUpwardsMovingPlatforms();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime, platforms);

        // Update the movement of each moving platform
        for (auto &movPlatform : movingPlatforms)
        {
            movPlatform.UpdateDownToUpMovement(deltaTime);
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        // Set up the background

        DrawTextureEx(worldMap, mapPosition, 0.0, 1.0, WHITE);

        player.Draw();

        for (auto &movPlatform : movingPlatforms)
        {
            // movPlatform.Draw();
             platform.DrawMovingTexture();
            // This moves the platform up and Down
            platform.mapPosition.y = movPlatform.mapPosition.y;
        }

        // Draw static platforms
        for (auto &staticPlatform : platforms)
        {
            // staticPlatform.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
