#include "raylib.h"
#include "config.h"
#include <vector>

class Platform {
public:
    Rectangle rect;
    bool isSolid;
    Texture2D upDownPlatformMap;
    Vector2 mapPosition;
    void InitializeTextures();

    bool movesUpAndDown;
    float minY; // Minimum Y position to move to
    float maxY; // Maximum Y position to move to
    float movingSpeed; // Speed of the up and down movement
    bool movingUp; //Checks if platform is moving upwards

    // default
    Platform();

    // Constructor for Platforms for collisions
    Platform(float x, float y, float width, float height);

    // Method to draw the platform
    void Draw();

    void DrawMovingTexture();

     void UpdateDownToUpMovement(float deltaTime);

    static std::vector<Platform> GetAllPlatforms();

    static std::vector<Platform> GetUpwardsMovingPlatforms();
   
};