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

Camera2D camera = { 0 };

// Clamp is created to prevent does what std::clamp does, but std was not available for some reason.  
template<typename T>
T Clamp(T value, T min, T max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    }
    return value;
}

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
    
    std::vector<Upgrade*> upgrades;

    float upgradeBoxX = 29.0f * config::tileSize; 
    float upgradeBoxY = windowHeight / 2.0f - 70; 

    upgrades.push_back(new LowGravityUpgrade(upgradeBoxX, upgradeBoxY, GREEN));

    camera.target = (Vector2){ player.position.x, player.position.y };
    camera.offset = (Vector2){ windowWidth / 2.0f, windowHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime, platforms, movingPlatforms);

        // Clamp stops the camera from going outside of the games bounds
        camera.target.x = Clamp(player.position.x, windowWidth / 2.0f, numTilesX * config::tileSize - windowWidth / 2.0f);
        camera.target.y = Clamp(player.position.y, windowHeight / 2.0f, numTilesY * config::tileSize - windowHeight / 2.0f);
        
        // Update the movement of each moving platform
        for (auto &movPlatform : movingPlatforms)
        {
            movPlatform.UpdateDownToUpMovement(deltaTime);
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        BeginMode2D(camera);

        // Set up the background

        DrawTextureEx(worldMap, mapPosition, 0.0, 1.0, WHITE);

        player.Draw();

        for (auto &movPlatform : movingPlatforms)
        {
             movPlatform.Draw();
             platform.DrawMovingTexture();
             //This moves the platform up and Down
            platform.mapPosition.y = movPlatform.mapPosition.y;
        }

        // Draw static platforms
        for (auto &staticPlatform : platforms)
        {
             staticPlatform.Draw();
        }

        for (auto& upgrade : upgrades) {
        upgrade->Draw();
        }

        for (auto& upgrade : upgrades) {
            if (upgrade->active && CheckCollisionRecs(player.getCollisionRec(), upgrade->GetCollisionRec())) {
                upgrade->ApplyEffect(player); // This will call LowGravityUpgrade::ApplyEffect
                upgrade->active = false; // Mark the upgrade as collected/inactive
            }
        }

        

        EndMode2D();

        EndDrawing();
    }
    
    for (auto& upgrade : upgrades) {
            delete upgrade;
        }
        upgrades.clear();

    CloseWindow();
    return 0;
}
